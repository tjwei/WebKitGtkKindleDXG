# -*- Mode: Python -*-

# GDBus - GLib D-Bus Library
#
# Copyright (C) 2008-2011 Red Hat, Inc.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General
# Public License along with this library; if not, write to the
# Free Software Foundation, Inc., 59 Temple Place, Suite 330,
# Boston, MA 02111-1307, USA.
#
# Author: David Zeuthen <davidz@redhat.com>

import sys
import xml.parsers.expat

from . import dbustypes

class DBusXMLParser:
    STATE_TOP = 'top'
    STATE_NODE = 'node'
    STATE_INTERFACE = 'interface'
    STATE_METHOD = 'method'
    STATE_SIGNAL = 'signal'
    STATE_PROPERTY = 'property'
    STATE_ARG = 'arg'
    STATE_ANNOTATION = 'annotation'
    STATE_IGNORED = 'ignored'

    def __init__(self, xml_data):
        self._parser = xml.parsers.expat.ParserCreate()
        self._parser.CommentHandler = self.handle_comment
        self._parser.CharacterDataHandler = self.handle_char_data
        self._parser.StartElementHandler = self.handle_start_element
        self._parser.EndElementHandler = self.handle_end_element

        self.parsed_interfaces = []
        self._cur_object = None

        self.state = DBusXMLParser.STATE_TOP
        self.state_stack = []
        self._cur_object = None
        self._cur_object_stack = []

        self.doc_comment_last_symbol = ''

        self._parser.Parse(xml_data)

    COMMENT_STATE_BEGIN = 'begin'
    COMMENT_STATE_PARAMS = 'params'
    COMMENT_STATE_BODY = 'body'
    COMMENT_STATE_SKIP = 'skip'
    def handle_comment(self, data):
        comment_state = DBusXMLParser.COMMENT_STATE_BEGIN;
        lines = data.split('\n')
        symbol = ''
        body = ''
        in_para = False
        params = {}
        for line in lines:
            orig_line = line
            line = line.lstrip()
            if comment_state == DBusXMLParser.COMMENT_STATE_BEGIN:
                if len(line) > 0:
                    colon_index = line.find(': ')
                    if colon_index == -1:
                        if line.endswith(':'):
                            symbol = line[0:len(line)-1]
                            comment_state = DBusXMLParser.COMMENT_STATE_PARAMS
                        else:
                            comment_state = DBusXMLParser.COMMENT_STATE_SKIP
                    else:
                        symbol = line[0:colon_index]
                        rest_of_line = line[colon_index+2:].strip()
                        if len(rest_of_line) > 0:
                            body += '<para>' + rest_of_line + '</para>'
                        comment_state = DBusXMLParser.COMMENT_STATE_PARAMS
            elif comment_state == DBusXMLParser.COMMENT_STATE_PARAMS:
                if line.startswith('@'):
                    colon_index = line.find(': ')
                    if colon_index == -1:
                        comment_state = DBusXMLParser.COMMENT_STATE_BODY
                        if not in_para:
                            body += '<para>'
                            in_para = True
                        body += orig_line + '\n'
                    else:
                        param = line[1:colon_index]
                        docs = line[colon_index + 2:]
                        params[param] = docs
                else:
                    comment_state = DBusXMLParser.COMMENT_STATE_BODY
                    if len(line) > 0:
                        if not in_para:
                            body += '<para>'
                            in_para = True
                        body += orig_line + '\n'
            elif comment_state == DBusXMLParser.COMMENT_STATE_BODY:
                if len(line) > 0:
                    if not in_para:
                        body += '<para>'
                        in_para = True
                    body += orig_line + '\n'
                else:
                    if in_para:
                        body += '</para>'
                        in_para = False
        if in_para:
            body += '</para>'

        if symbol != '':
            self.doc_comment_last_symbol = symbol
            self.doc_comment_params = params
            self.doc_comment_body = body

    def handle_char_data(self, data):
        #print 'char_data=%s'%data
        pass

    def handle_start_element(self, name, attrs):
        old_state = self.state
        old_cur_object = self._cur_object
        if self.state == DBusXMLParser.STATE_IGNORED:
            self.state = DBusXMLParser.STATE_IGNORED
        elif self.state == DBusXMLParser.STATE_TOP:
            if name == DBusXMLParser.STATE_NODE:
                self.state = DBusXMLParser.STATE_NODE
            else:
                self.state = DBusXMLParser.STATE_IGNORED
        elif self.state == DBusXMLParser.STATE_NODE:
            if name == DBusXMLParser.STATE_INTERFACE:
                self.state = DBusXMLParser.STATE_INTERFACE
                iface = dbustypes.Interface(attrs['name'])
                self._cur_object = iface
                self.parsed_interfaces.append(iface)
            elif name == DBusXMLParser.STATE_ANNOTATION:
                self.state = DBusXMLParser.STATE_ANNOTATION
                anno = dbustypes.Annotation(attrs['name'], attrs['value'])
                self._cur_object.annotations.append(anno)
                self._cur_object = anno
            else:
                self.state = DBusXMLParser.STATE_IGNORED

            # assign docs, if any
            if attrs.has_key('name') and self.doc_comment_last_symbol == attrs['name']:
                self._cur_object.doc_string = self.doc_comment_body
                if self.doc_comment_params.has_key('short_description'):
                    short_description = self.doc_comment_params['short_description']
                    self._cur_object.doc_string_brief = short_description
                if self.doc_comment_params.has_key('since'):
                    self._cur_object.since = self.doc_comment_params['since']

        elif self.state == DBusXMLParser.STATE_INTERFACE:
            if name == DBusXMLParser.STATE_METHOD:
                self.state = DBusXMLParser.STATE_METHOD
                method = dbustypes.Method(attrs['name'])
                self._cur_object.methods.append(method)
                self._cur_object = method
            elif name == DBusXMLParser.STATE_SIGNAL:
                self.state = DBusXMLParser.STATE_SIGNAL
                signal = dbustypes.Signal(attrs['name'])
                self._cur_object.signals.append(signal)
                self._cur_object = signal
            elif name == DBusXMLParser.STATE_PROPERTY:
                self.state = DBusXMLParser.STATE_PROPERTY
                prop = dbustypes.Property(attrs['name'], attrs['type'], attrs['access'])
                self._cur_object.properties.append(prop)
                self._cur_object = prop
            elif name == DBusXMLParser.STATE_ANNOTATION:
                self.state = DBusXMLParser.STATE_ANNOTATION
                anno = dbustypes.Annotation(attrs['name'], attrs['value'])
                self._cur_object.annotations.append(anno)
                self._cur_object = anno
            else:
                self.state = DBusXMLParser.STATE_IGNORED

            # assign docs, if any
            if attrs.has_key('name') and self.doc_comment_last_symbol == attrs['name']:
                self._cur_object.doc_string = self.doc_comment_body
                if self.doc_comment_params.has_key('since'):
                    self._cur_object.since = self.doc_comment_params['since']

        elif self.state == DBusXMLParser.STATE_METHOD:
            if name == DBusXMLParser.STATE_ARG:
                self.state = DBusXMLParser.STATE_ARG
                arg_name = None
                if attrs.has_key('name'):
                    arg_name = attrs['name']
                arg = dbustypes.Arg(arg_name, attrs['type'])
                direction = attrs['direction']
                if direction == 'in':
                    self._cur_object.in_args.append(arg)
                elif direction == 'out':
                    self._cur_object.out_args.append(arg)
                else:
                    raise RuntimeError('Invalid direction "%s"'%(direction))
                self._cur_object = arg
            elif name == DBusXMLParser.STATE_ANNOTATION:
                self.state = DBusXMLParser.STATE_ANNOTATION
                anno = dbustypes.Annotation(attrs['name'], attrs['value'])
                self._cur_object.annotations.append(anno)
                self._cur_object = anno
            else:
                self.state = DBusXMLParser.STATE_IGNORED

            # assign docs, if any
            if self.doc_comment_last_symbol == old_cur_object.name:
                if attrs.has_key('name') and self.doc_comment_params.has_key(attrs['name']):
                    doc_string = self.doc_comment_params[attrs['name']]
                    if doc_string != None:
                        self._cur_object.doc_string = doc_string
                    if self.doc_comment_params.has_key('since'):
                        self._cur_object.since = self.doc_comment_params['since']

        elif self.state == DBusXMLParser.STATE_SIGNAL:
            if name == DBusXMLParser.STATE_ARG:
                self.state = DBusXMLParser.STATE_ARG
                arg_name = None
                if attrs.has_key('name'):
                    arg_name = attrs['name']
                arg = dbustypes.Arg(arg_name, attrs['type'])
                self._cur_object.args.append(arg)
                self._cur_object = arg
            elif name == DBusXMLParser.STATE_ANNOTATION:
                self.state = DBusXMLParser.STATE_ANNOTATION
                anno = dbustypes.Annotation(attrs['name'], attrs['value'])
                self._cur_object.annotations.append(anno)
                self._cur_object = anno
            else:
                self.state = DBusXMLParser.STATE_IGNORED

            # assign docs, if any
            if self.doc_comment_last_symbol == old_cur_object.name:
                if attrs.has_key('name') and self.doc_comment_params.has_key(attrs['name']):
                    doc_string = self.doc_comment_params[attrs['name']]
                    if doc_string != None:
                        self._cur_object.doc_string = doc_string
                    if self.doc_comment_params.has_key('since'):
                        self._cur_object.since = self.doc_comment_params['since']

        elif self.state == DBusXMLParser.STATE_PROPERTY:
            if name == DBusXMLParser.STATE_ANNOTATION:
                self.state = DBusXMLParser.STATE_ANNOTATION
                anno = dbustypes.Annotation(attrs['name'], attrs['value'])
                self._cur_object.annotations.append(anno)
                self._cur_object = anno
            else:
                self.state = DBusXMLParser.STATE_IGNORED

        elif self.state == DBusXMLParser.STATE_ARG:
            if name == DBusXMLParser.STATE_ANNOTATION:
                self.state = DBusXMLParser.STATE_ANNOTATION
                anno = dbustypes.Annotation(attrs['name'], attrs['value'])
                self._cur_object.annotations.append(anno)
                self._cur_object = anno
            else:
                self.state = DBusXMLParser.STATE_IGNORED

        elif self.state == DBusXMLParser.STATE_ANNOTATION:
            if name == DBusXMLParser.STATE_ANNOTATION:
                self.state = DBusXMLParser.STATE_ANNOTATION
                anno = dbustypes.Annotation(attrs['name'], attrs['value'])
                self._cur_object.annotations.append(anno)
                self._cur_object = anno
            else:
                self.state = DBusXMLParser.STATE_IGNORED

        else:
            raise RuntimeError('Unhandled state "%s" while entering element with name "%s"'%(self.state, name))

        self.state_stack.append(old_state)
        self._cur_object_stack.append(old_cur_object)

    def handle_end_element(self, name):
        self.state = self.state_stack.pop()
        self._cur_object = self._cur_object_stack.pop()

def parse_dbus_xml(xml_data):
    parser = DBusXMLParser(xml_data)
    return parser.parsed_interfaces

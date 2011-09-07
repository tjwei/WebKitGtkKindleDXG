/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"

#include "JSHTMLTextAreaElement.h"

#include <wtf/GetPtr.h>

#include "HTMLFormElement.h"
#include "HTMLTextAreaElement.h"
#include "JSHTMLFormElement.h"
#include "KURL.h"

#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>
#include <runtime/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSHTMLTextAreaElement);

/* Hash table */

static const HashTableValue JSHTMLTextAreaElementTableValues[16] =
{
    { "defaultValue", DontDelete, (intptr_t)jsHTMLTextAreaElementDefaultValue, (intptr_t)setJSHTMLTextAreaElementDefaultValue },
    { "form", DontDelete|ReadOnly, (intptr_t)jsHTMLTextAreaElementForm, (intptr_t)0 },
    { "accessKey", DontDelete, (intptr_t)jsHTMLTextAreaElementAccessKey, (intptr_t)setJSHTMLTextAreaElementAccessKey },
    { "cols", DontDelete, (intptr_t)jsHTMLTextAreaElementCols, (intptr_t)setJSHTMLTextAreaElementCols },
    { "disabled", DontDelete, (intptr_t)jsHTMLTextAreaElementDisabled, (intptr_t)setJSHTMLTextAreaElementDisabled },
    { "autofocus", DontDelete, (intptr_t)jsHTMLTextAreaElementAutofocus, (intptr_t)setJSHTMLTextAreaElementAutofocus },
    { "name", DontDelete, (intptr_t)jsHTMLTextAreaElementName, (intptr_t)setJSHTMLTextAreaElementName },
    { "readOnly", DontDelete, (intptr_t)jsHTMLTextAreaElementReadOnly, (intptr_t)setJSHTMLTextAreaElementReadOnly },
    { "rows", DontDelete, (intptr_t)jsHTMLTextAreaElementRows, (intptr_t)setJSHTMLTextAreaElementRows },
    { "type", DontDelete|ReadOnly, (intptr_t)jsHTMLTextAreaElementType, (intptr_t)0 },
    { "value", DontDelete, (intptr_t)jsHTMLTextAreaElementValue, (intptr_t)setJSHTMLTextAreaElementValue },
    { "willValidate", DontDelete|ReadOnly, (intptr_t)jsHTMLTextAreaElementWillValidate, (intptr_t)0 },
    { "selectionStart", DontDelete, (intptr_t)jsHTMLTextAreaElementSelectionStart, (intptr_t)setJSHTMLTextAreaElementSelectionStart },
    { "selectionEnd", DontDelete, (intptr_t)jsHTMLTextAreaElementSelectionEnd, (intptr_t)setJSHTMLTextAreaElementSelectionEnd },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsHTMLTextAreaElementConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLTextAreaElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 255, JSHTMLTextAreaElementTableValues, 0 };
#else
    { 35, 31, JSHTMLTextAreaElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSHTMLTextAreaElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLTextAreaElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLTextAreaElementConstructorTableValues, 0 };
#else
    { 1, 0, JSHTMLTextAreaElementConstructorTableValues, 0 };
#endif

class JSHTMLTextAreaElementConstructor : public DOMObject {
public:
    JSHTMLTextAreaElementConstructor(ExecState* exec)
        : DOMObject(JSHTMLTextAreaElementConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSHTMLTextAreaElementPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSHTMLTextAreaElementConstructor::s_info = { "HTMLTextAreaElementConstructor", 0, &JSHTMLTextAreaElementConstructorTable, 0 };

bool JSHTMLTextAreaElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLTextAreaElementConstructor, DOMObject>(exec, &JSHTMLTextAreaElementConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSHTMLTextAreaElementPrototypeTableValues[3] =
{
    { "select", DontDelete|Function, (intptr_t)jsHTMLTextAreaElementPrototypeFunctionSelect, (intptr_t)0 },
    { "setSelectionRange", DontDelete|Function, (intptr_t)jsHTMLTextAreaElementPrototypeFunctionSetSelectionRange, (intptr_t)2 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLTextAreaElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSHTMLTextAreaElementPrototypeTableValues, 0 };
#else
    { 5, 3, JSHTMLTextAreaElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSHTMLTextAreaElementPrototype::s_info = { "HTMLTextAreaElementPrototype", 0, &JSHTMLTextAreaElementPrototypeTable, 0 };

JSObject* JSHTMLTextAreaElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSHTMLTextAreaElement>(exec, globalObject);
}

bool JSHTMLTextAreaElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSHTMLTextAreaElementPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSHTMLTextAreaElement::s_info = { "HTMLTextAreaElement", &JSHTMLElement::s_info, &JSHTMLTextAreaElementTable, 0 };

JSHTMLTextAreaElement::JSHTMLTextAreaElement(PassRefPtr<Structure> structure, PassRefPtr<HTMLTextAreaElement> impl)
    : JSHTMLElement(structure, impl)
{
}

JSObject* JSHTMLTextAreaElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSHTMLTextAreaElementPrototype(JSHTMLTextAreaElementPrototype::createStructure(JSHTMLElementPrototype::self(exec, globalObject)));
}

bool JSHTMLTextAreaElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLTextAreaElement, Base>(exec, &JSHTMLTextAreaElementTable, this, propertyName, slot);
}

JSValue jsHTMLTextAreaElementDefaultValue(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->defaultValue());
}

JSValue jsHTMLTextAreaElementForm(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->form()));
}

JSValue jsHTMLTextAreaElementAccessKey(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->accessKey());
}

JSValue jsHTMLTextAreaElementCols(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->cols());
}

JSValue jsHTMLTextAreaElementDisabled(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->disabled());
}

JSValue jsHTMLTextAreaElementAutofocus(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->autofocus());
}

JSValue jsHTMLTextAreaElementName(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->name());
}

JSValue jsHTMLTextAreaElementReadOnly(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->readOnly());
}

JSValue jsHTMLTextAreaElementRows(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->rows());
}

JSValue jsHTMLTextAreaElementType(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->type());
}

JSValue jsHTMLTextAreaElementValue(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->value());
}

JSValue jsHTMLTextAreaElementWillValidate(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->willValidate());
}

JSValue jsHTMLTextAreaElementSelectionStart(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->selectionStart());
}

JSValue jsHTMLTextAreaElementSelectionEnd(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->selectionEnd());
}

JSValue jsHTMLTextAreaElementConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSHTMLTextAreaElement*>(asObject(slot.slotBase()))->getConstructor(exec);
}
void JSHTMLTextAreaElement::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSHTMLTextAreaElement, Base>(exec, propertyName, value, &JSHTMLTextAreaElementTable, this, slot);
}

void setJSHTMLTextAreaElementDefaultValue(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(thisObject)->impl());
    imp->setDefaultValue(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLTextAreaElementAccessKey(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(thisObject)->impl());
    imp->setAccessKey(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLTextAreaElementCols(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(thisObject)->impl());
    imp->setCols(value.toInt32(exec));
}

void setJSHTMLTextAreaElementDisabled(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(thisObject)->impl());
    imp->setDisabled(value.toBoolean(exec));
}

void setJSHTMLTextAreaElementAutofocus(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(thisObject)->impl());
    imp->setAutofocus(value.toBoolean(exec));
}

void setJSHTMLTextAreaElementName(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(thisObject)->impl());
    imp->setName(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLTextAreaElementReadOnly(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(thisObject)->impl());
    imp->setReadOnly(value.toBoolean(exec));
}

void setJSHTMLTextAreaElementRows(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(thisObject)->impl());
    imp->setRows(value.toInt32(exec));
}

void setJSHTMLTextAreaElementValue(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(thisObject)->impl());
    imp->setValue(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLTextAreaElementSelectionStart(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(thisObject)->impl());
    imp->setSelectionStart(value.toInt32(exec));
}

void setJSHTMLTextAreaElementSelectionEnd(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(static_cast<JSHTMLTextAreaElement*>(thisObject)->impl());
    imp->setSelectionEnd(value.toInt32(exec));
}

JSValue JSHTMLTextAreaElement::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSHTMLTextAreaElementConstructor>(exec);
}

JSValue JSC_HOST_CALL jsHTMLTextAreaElementPrototypeFunctionSelect(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSHTMLTextAreaElement::s_info))
        return throwError(exec, TypeError);
    JSHTMLTextAreaElement* castedThisObj = static_cast<JSHTMLTextAreaElement*>(asObject(thisValue));
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(castedThisObj->impl());

    imp->select();
    return jsUndefined();
}

JSValue JSC_HOST_CALL jsHTMLTextAreaElementPrototypeFunctionSetSelectionRange(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSHTMLTextAreaElement::s_info))
        return throwError(exec, TypeError);
    JSHTMLTextAreaElement* castedThisObj = static_cast<JSHTMLTextAreaElement*>(asObject(thisValue));
    HTMLTextAreaElement* imp = static_cast<HTMLTextAreaElement*>(castedThisObj->impl());
    int start = args.at(0).toInt32(exec);
    int end = args.at(1).toInt32(exec);

    imp->setSelectionRange(start, end);
    return jsUndefined();
}


}

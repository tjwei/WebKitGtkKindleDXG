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

#include "JSComment.h"

#include <wtf/GetPtr.h>

#include "Comment.h"

#include <runtime/JSNumberCell.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSComment);

/* Hash table */

static const HashTableValue JSCommentTableValues[2] =
{
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsCommentConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSCommentTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSCommentTableValues, 0 };
#else
    { 2, 1, JSCommentTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSCommentConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSCommentConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSCommentConstructorTableValues, 0 };
#else
    { 1, 0, JSCommentConstructorTableValues, 0 };
#endif

class JSCommentConstructor : public DOMObject {
public:
    JSCommentConstructor(ExecState* exec)
        : DOMObject(JSCommentConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSCommentPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSCommentConstructor::s_info = { "CommentConstructor", 0, &JSCommentConstructorTable, 0 };

bool JSCommentConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSCommentConstructor, DOMObject>(exec, &JSCommentConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSCommentPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSCommentPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSCommentPrototypeTableValues, 0 };
#else
    { 1, 0, JSCommentPrototypeTableValues, 0 };
#endif

const ClassInfo JSCommentPrototype::s_info = { "CommentPrototype", 0, &JSCommentPrototypeTable, 0 };

JSObject* JSCommentPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSComment>(exec, globalObject);
}

const ClassInfo JSComment::s_info = { "Comment", &JSCharacterData::s_info, &JSCommentTable, 0 };

JSComment::JSComment(PassRefPtr<Structure> structure, PassRefPtr<Comment> impl)
    : JSCharacterData(structure, impl)
{
}

JSObject* JSComment::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSCommentPrototype(JSCommentPrototype::createStructure(JSCharacterDataPrototype::self(exec, globalObject)));
}

bool JSComment::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSComment, Base>(exec, &JSCommentTable, this, propertyName, slot);
}

JSValue jsCommentConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSComment*>(asObject(slot.slotBase()))->getConstructor(exec);
}
JSValue JSComment::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSCommentConstructor>(exec);
}


}

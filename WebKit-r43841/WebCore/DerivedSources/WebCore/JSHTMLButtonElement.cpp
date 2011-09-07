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

#include "JSHTMLButtonElement.h"

#include <wtf/GetPtr.h>

#include "HTMLButtonElement.h"
#include "HTMLFormElement.h"
#include "JSHTMLFormElement.h"
#include "KURL.h"

#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>
#include <runtime/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSHTMLButtonElement);

/* Hash table */

static const HashTableValue JSHTMLButtonElementTableValues[10] =
{
    { "form", DontDelete|ReadOnly, (intptr_t)jsHTMLButtonElementForm, (intptr_t)0 },
    { "accessKey", DontDelete, (intptr_t)jsHTMLButtonElementAccessKey, (intptr_t)setJSHTMLButtonElementAccessKey },
    { "disabled", DontDelete, (intptr_t)jsHTMLButtonElementDisabled, (intptr_t)setJSHTMLButtonElementDisabled },
    { "autofocus", DontDelete, (intptr_t)jsHTMLButtonElementAutofocus, (intptr_t)setJSHTMLButtonElementAutofocus },
    { "name", DontDelete, (intptr_t)jsHTMLButtonElementName, (intptr_t)setJSHTMLButtonElementName },
    { "type", DontDelete|ReadOnly, (intptr_t)jsHTMLButtonElementType, (intptr_t)0 },
    { "value", DontDelete, (intptr_t)jsHTMLButtonElementValue, (intptr_t)setJSHTMLButtonElementValue },
    { "willValidate", DontDelete|ReadOnly, (intptr_t)jsHTMLButtonElementWillValidate, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsHTMLButtonElementConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLButtonElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 127, JSHTMLButtonElementTableValues, 0 };
#else
    { 33, 31, JSHTMLButtonElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSHTMLButtonElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLButtonElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLButtonElementConstructorTableValues, 0 };
#else
    { 1, 0, JSHTMLButtonElementConstructorTableValues, 0 };
#endif

class JSHTMLButtonElementConstructor : public DOMObject {
public:
    JSHTMLButtonElementConstructor(ExecState* exec)
        : DOMObject(JSHTMLButtonElementConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSHTMLButtonElementPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSHTMLButtonElementConstructor::s_info = { "HTMLButtonElementConstructor", 0, &JSHTMLButtonElementConstructorTable, 0 };

bool JSHTMLButtonElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLButtonElementConstructor, DOMObject>(exec, &JSHTMLButtonElementConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSHTMLButtonElementPrototypeTableValues[2] =
{
    { "click", DontDelete|Function, (intptr_t)jsHTMLButtonElementPrototypeFunctionClick, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLButtonElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLButtonElementPrototypeTableValues, 0 };
#else
    { 2, 1, JSHTMLButtonElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSHTMLButtonElementPrototype::s_info = { "HTMLButtonElementPrototype", 0, &JSHTMLButtonElementPrototypeTable, 0 };

JSObject* JSHTMLButtonElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSHTMLButtonElement>(exec, globalObject);
}

bool JSHTMLButtonElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSHTMLButtonElementPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSHTMLButtonElement::s_info = { "HTMLButtonElement", &JSHTMLElement::s_info, &JSHTMLButtonElementTable, 0 };

JSHTMLButtonElement::JSHTMLButtonElement(PassRefPtr<Structure> structure, PassRefPtr<HTMLButtonElement> impl)
    : JSHTMLElement(structure, impl)
{
}

JSObject* JSHTMLButtonElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSHTMLButtonElementPrototype(JSHTMLButtonElementPrototype::createStructure(JSHTMLElementPrototype::self(exec, globalObject)));
}

bool JSHTMLButtonElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLButtonElement, Base>(exec, &JSHTMLButtonElementTable, this, propertyName, slot);
}

JSValue jsHTMLButtonElementForm(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLButtonElement* imp = static_cast<HTMLButtonElement*>(static_cast<JSHTMLButtonElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->form()));
}

JSValue jsHTMLButtonElementAccessKey(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLButtonElement* imp = static_cast<HTMLButtonElement*>(static_cast<JSHTMLButtonElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->accessKey());
}

JSValue jsHTMLButtonElementDisabled(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLButtonElement* imp = static_cast<HTMLButtonElement*>(static_cast<JSHTMLButtonElement*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->disabled());
}

JSValue jsHTMLButtonElementAutofocus(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLButtonElement* imp = static_cast<HTMLButtonElement*>(static_cast<JSHTMLButtonElement*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->autofocus());
}

JSValue jsHTMLButtonElementName(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLButtonElement* imp = static_cast<HTMLButtonElement*>(static_cast<JSHTMLButtonElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->name());
}

JSValue jsHTMLButtonElementType(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLButtonElement* imp = static_cast<HTMLButtonElement*>(static_cast<JSHTMLButtonElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->type());
}

JSValue jsHTMLButtonElementValue(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLButtonElement* imp = static_cast<HTMLButtonElement*>(static_cast<JSHTMLButtonElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->value());
}

JSValue jsHTMLButtonElementWillValidate(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLButtonElement* imp = static_cast<HTMLButtonElement*>(static_cast<JSHTMLButtonElement*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->willValidate());
}

JSValue jsHTMLButtonElementConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSHTMLButtonElement*>(asObject(slot.slotBase()))->getConstructor(exec);
}
void JSHTMLButtonElement::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSHTMLButtonElement, Base>(exec, propertyName, value, &JSHTMLButtonElementTable, this, slot);
}

void setJSHTMLButtonElementAccessKey(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLButtonElement* imp = static_cast<HTMLButtonElement*>(static_cast<JSHTMLButtonElement*>(thisObject)->impl());
    imp->setAccessKey(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLButtonElementDisabled(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLButtonElement* imp = static_cast<HTMLButtonElement*>(static_cast<JSHTMLButtonElement*>(thisObject)->impl());
    imp->setDisabled(value.toBoolean(exec));
}

void setJSHTMLButtonElementAutofocus(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLButtonElement* imp = static_cast<HTMLButtonElement*>(static_cast<JSHTMLButtonElement*>(thisObject)->impl());
    imp->setAutofocus(value.toBoolean(exec));
}

void setJSHTMLButtonElementName(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLButtonElement* imp = static_cast<HTMLButtonElement*>(static_cast<JSHTMLButtonElement*>(thisObject)->impl());
    imp->setName(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLButtonElementValue(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLButtonElement* imp = static_cast<HTMLButtonElement*>(static_cast<JSHTMLButtonElement*>(thisObject)->impl());
    imp->setValue(valueToStringWithNullCheck(exec, value));
}

JSValue JSHTMLButtonElement::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSHTMLButtonElementConstructor>(exec);
}

JSValue JSC_HOST_CALL jsHTMLButtonElementPrototypeFunctionClick(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSHTMLButtonElement::s_info))
        return throwError(exec, TypeError);
    JSHTMLButtonElement* castedThisObj = static_cast<JSHTMLButtonElement*>(asObject(thisValue));
    HTMLButtonElement* imp = static_cast<HTMLButtonElement*>(castedThisObj->impl());

    imp->click();
    return jsUndefined();
}


}

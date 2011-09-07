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

#include "JSHTMLSelectElement.h"

#include <wtf/GetPtr.h>

#include <runtime/PropertyNameArray.h>
#include "ExceptionCode.h"
#include "HTMLFormElement.h"
#include "HTMLOptionsCollection.h"
#include "HTMLSelectElement.h"
#include "JSHTMLElement.h"
#include "JSHTMLFormElement.h"
#include "JSHTMLOptionsCollection.h"
#include "JSNode.h"
#include "KURL.h"
#include "Node.h"

#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>
#include <runtime/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSHTMLSelectElement);

/* Hash table */

static const HashTableValue JSHTMLSelectElementTableValues[14] =
{
    { "type", DontDelete|ReadOnly, (intptr_t)jsHTMLSelectElementType, (intptr_t)0 },
    { "selectedIndex", DontDelete, (intptr_t)jsHTMLSelectElementSelectedIndex, (intptr_t)setJSHTMLSelectElementSelectedIndex },
    { "value", DontDelete, (intptr_t)jsHTMLSelectElementValue, (intptr_t)setJSHTMLSelectElementValue },
    { "length", DontDelete, (intptr_t)jsHTMLSelectElementLength, (intptr_t)setJSHTMLSelectElementLength },
    { "form", DontDelete|ReadOnly, (intptr_t)jsHTMLSelectElementForm, (intptr_t)0 },
    { "willValidate", DontDelete|ReadOnly, (intptr_t)jsHTMLSelectElementWillValidate, (intptr_t)0 },
    { "options", DontDelete|ReadOnly, (intptr_t)jsHTMLSelectElementOptions, (intptr_t)0 },
    { "disabled", DontDelete, (intptr_t)jsHTMLSelectElementDisabled, (intptr_t)setJSHTMLSelectElementDisabled },
    { "autofocus", DontDelete, (intptr_t)jsHTMLSelectElementAutofocus, (intptr_t)setJSHTMLSelectElementAutofocus },
    { "multiple", DontDelete, (intptr_t)jsHTMLSelectElementMultiple, (intptr_t)setJSHTMLSelectElementMultiple },
    { "name", DontDelete, (intptr_t)jsHTMLSelectElementName, (intptr_t)setJSHTMLSelectElementName },
    { "size", DontDelete, (intptr_t)jsHTMLSelectElementSize, (intptr_t)setJSHTMLSelectElementSize },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsHTMLSelectElementConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLSelectElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 127, JSHTMLSelectElementTableValues, 0 };
#else
    { 34, 31, JSHTMLSelectElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSHTMLSelectElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLSelectElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLSelectElementConstructorTableValues, 0 };
#else
    { 1, 0, JSHTMLSelectElementConstructorTableValues, 0 };
#endif

class JSHTMLSelectElementConstructor : public DOMObject {
public:
    JSHTMLSelectElementConstructor(ExecState* exec)
        : DOMObject(JSHTMLSelectElementConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSHTMLSelectElementPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSHTMLSelectElementConstructor::s_info = { "HTMLSelectElementConstructor", 0, &JSHTMLSelectElementConstructorTable, 0 };

bool JSHTMLSelectElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLSelectElementConstructor, DOMObject>(exec, &JSHTMLSelectElementConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSHTMLSelectElementPrototypeTableValues[5] =
{
    { "add", DontDelete|Function, (intptr_t)jsHTMLSelectElementPrototypeFunctionAdd, (intptr_t)2 },
    { "remove", DontDelete|Function, (intptr_t)jsHTMLSelectElementPrototypeFunctionRemove, (intptr_t)0 },
    { "item", DontDelete|Function, (intptr_t)jsHTMLSelectElementPrototypeFunctionItem, (intptr_t)1 },
    { "namedItem", DontDelete|Function, (intptr_t)jsHTMLSelectElementPrototypeFunctionNamedItem, (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLSelectElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSHTMLSelectElementPrototypeTableValues, 0 };
#else
    { 9, 7, JSHTMLSelectElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSHTMLSelectElementPrototype::s_info = { "HTMLSelectElementPrototype", 0, &JSHTMLSelectElementPrototypeTable, 0 };

JSObject* JSHTMLSelectElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSHTMLSelectElement>(exec, globalObject);
}

bool JSHTMLSelectElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSHTMLSelectElementPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSHTMLSelectElement::s_info = { "HTMLSelectElement", &JSHTMLElement::s_info, &JSHTMLSelectElementTable, 0 };

JSHTMLSelectElement::JSHTMLSelectElement(PassRefPtr<Structure> structure, PassRefPtr<HTMLSelectElement> impl)
    : JSHTMLElement(structure, impl)
{
}

JSObject* JSHTMLSelectElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSHTMLSelectElementPrototype(JSHTMLSelectElementPrototype::createStructure(JSHTMLElementPrototype::self(exec, globalObject)));
}

bool JSHTMLSelectElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    const HashEntry* entry = JSHTMLSelectElementTable.entry(exec, propertyName);
    if (entry) {
        slot.setCustom(this, entry->propertyGetter());
        return true;
    }
    bool ok;
    unsigned index = propertyName.toUInt32(&ok, false);
    if (ok && index < static_cast<HTMLSelectElement*>(impl())->length()) {
        slot.setCustomIndex(this, index, indexGetter);
        return true;
    }
    return getStaticValueSlot<JSHTMLSelectElement, Base>(exec, &JSHTMLSelectElementTable, this, propertyName, slot);
}

bool JSHTMLSelectElement::getOwnPropertySlot(ExecState* exec, unsigned propertyName, PropertySlot& slot)
{
    if (propertyName < static_cast<HTMLSelectElement*>(impl())->length()) {
        slot.setCustomIndex(this, propertyName, indexGetter);
        return true;
    }
    return getOwnPropertySlot(exec, Identifier::from(exec, propertyName), slot);
}

JSValue jsHTMLSelectElementType(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->type());
}

JSValue jsHTMLSelectElementSelectedIndex(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->selectedIndex());
}

JSValue jsHTMLSelectElementValue(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->value());
}

JSValue jsHTMLSelectElementLength(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->length());
}

JSValue jsHTMLSelectElementForm(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->form()));
}

JSValue jsHTMLSelectElementWillValidate(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->willValidate());
}

JSValue jsHTMLSelectElementOptions(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->options()));
}

JSValue jsHTMLSelectElementDisabled(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->disabled());
}

JSValue jsHTMLSelectElementAutofocus(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->autofocus());
}

JSValue jsHTMLSelectElementMultiple(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->multiple());
}

JSValue jsHTMLSelectElementName(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->name());
}

JSValue jsHTMLSelectElementSize(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->size());
}

JSValue jsHTMLSelectElementConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSHTMLSelectElement*>(asObject(slot.slotBase()))->getConstructor(exec);
}
void JSHTMLSelectElement::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    bool ok;
    unsigned index = propertyName.toUInt32(&ok, false);
    if (ok) {
        indexSetter(exec, index, value);
        return;
    }
    lookupPut<JSHTMLSelectElement, Base>(exec, propertyName, value, &JSHTMLSelectElementTable, this, slot);
}

void JSHTMLSelectElement::put(ExecState* exec, unsigned propertyName, JSValue value)
{
    indexSetter(exec, propertyName, value);
    return;
}

void setJSHTMLSelectElementSelectedIndex(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(thisObject)->impl());
    imp->setSelectedIndex(value.toInt32(exec));
}

void setJSHTMLSelectElementValue(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(thisObject)->impl());
    imp->setValue(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLSelectElementLength(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(thisObject)->impl());
    ExceptionCode ec = 0;
    imp->setLength(value.toInt32(exec), ec);
    setDOMException(exec, ec);
}

void setJSHTMLSelectElementDisabled(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(thisObject)->impl());
    imp->setDisabled(value.toBoolean(exec));
}

void setJSHTMLSelectElementAutofocus(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(thisObject)->impl());
    imp->setAutofocus(value.toBoolean(exec));
}

void setJSHTMLSelectElementMultiple(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(thisObject)->impl());
    imp->setMultiple(value.toBoolean(exec));
}

void setJSHTMLSelectElementName(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(thisObject)->impl());
    imp->setName(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLSelectElementSize(ExecState* exec, JSObject* thisObject, JSValue value)
{
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(static_cast<JSHTMLSelectElement*>(thisObject)->impl());
    imp->setSize(value.toInt32(exec));
}

void JSHTMLSelectElement::getPropertyNames(ExecState* exec, PropertyNameArray& propertyNames)
{
    for (unsigned i = 0; i < static_cast<HTMLSelectElement*>(impl())->length(); ++i)
        propertyNames.add(Identifier::from(exec, i));
     Base::getPropertyNames(exec, propertyNames);
}

JSValue JSHTMLSelectElement::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSHTMLSelectElementConstructor>(exec);
}

JSValue JSC_HOST_CALL jsHTMLSelectElementPrototypeFunctionAdd(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSHTMLSelectElement::s_info))
        return throwError(exec, TypeError);
    JSHTMLSelectElement* castedThisObj = static_cast<JSHTMLSelectElement*>(asObject(thisValue));
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(castedThisObj->impl());
    ExceptionCode ec = 0;
    HTMLElement* element = toHTMLElement(args.at(0));
    HTMLElement* before = toHTMLElement(args.at(1));

    imp->add(element, before, ec);
    setDOMException(exec, ec);
    return jsUndefined();
}

JSValue JSC_HOST_CALL jsHTMLSelectElementPrototypeFunctionRemove(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSHTMLSelectElement::s_info))
        return throwError(exec, TypeError);
    JSHTMLSelectElement* castedThisObj = static_cast<JSHTMLSelectElement*>(asObject(thisValue));
    return castedThisObj->remove(exec, args);
}

JSValue JSC_HOST_CALL jsHTMLSelectElementPrototypeFunctionItem(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSHTMLSelectElement::s_info))
        return throwError(exec, TypeError);
    JSHTMLSelectElement* castedThisObj = static_cast<JSHTMLSelectElement*>(asObject(thisValue));
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(castedThisObj->impl());
    int index = args.at(0).toInt32(exec);
    if (index < 0) {
        setDOMException(exec, INDEX_SIZE_ERR);
        return jsUndefined();
    }


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->item(index)));
    return result;
}

JSValue JSC_HOST_CALL jsHTMLSelectElementPrototypeFunctionNamedItem(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSHTMLSelectElement::s_info))
        return throwError(exec, TypeError);
    JSHTMLSelectElement* castedThisObj = static_cast<JSHTMLSelectElement*>(asObject(thisValue));
    HTMLSelectElement* imp = static_cast<HTMLSelectElement*>(castedThisObj->impl());
    const UString& name = args.at(0).toString(exec);


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->namedItem(name)));
    return result;
}


JSValue JSHTMLSelectElement::indexGetter(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    JSHTMLSelectElement* thisObj = static_cast<JSHTMLSelectElement*>(asObject(slot.slotBase()));
    return toJS(exec, static_cast<HTMLSelectElement*>(thisObj->impl())->item(slot.index()));
}

}

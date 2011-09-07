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

#include "JSDOMImplementation.h"

#include <wtf/GetPtr.h>

#include "CSSStyleSheet.h"
#include "DOMImplementation.h"
#include "Document.h"
#include "DocumentType.h"
#include "HTMLDocument.h"
#include "JSCSSStyleSheet.h"
#include "JSDocument.h"
#include "JSDocumentType.h"
#include "JSHTMLDocument.h"
#include "NodeFilter.h"

#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSDOMImplementation);

/* Hash table */

static const HashTableValue JSDOMImplementationTableValues[2] =
{
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsDOMImplementationConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSDOMImplementationTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSDOMImplementationTableValues, 0 };
#else
    { 2, 1, JSDOMImplementationTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSDOMImplementationConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSDOMImplementationConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSDOMImplementationConstructorTableValues, 0 };
#else
    { 1, 0, JSDOMImplementationConstructorTableValues, 0 };
#endif

class JSDOMImplementationConstructor : public DOMObject {
public:
    JSDOMImplementationConstructor(ExecState* exec)
        : DOMObject(JSDOMImplementationConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSDOMImplementationPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSDOMImplementationConstructor::s_info = { "DOMImplementationConstructor", 0, &JSDOMImplementationConstructorTable, 0 };

bool JSDOMImplementationConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSDOMImplementationConstructor, DOMObject>(exec, &JSDOMImplementationConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSDOMImplementationPrototypeTableValues[6] =
{
    { "hasFeature", DontDelete|Function, (intptr_t)jsDOMImplementationPrototypeFunctionHasFeature, (intptr_t)2 },
    { "createDocumentType", DontDelete|Function, (intptr_t)jsDOMImplementationPrototypeFunctionCreateDocumentType, (intptr_t)3 },
    { "createDocument", DontDelete|Function, (intptr_t)jsDOMImplementationPrototypeFunctionCreateDocument, (intptr_t)3 },
    { "createCSSStyleSheet", DontDelete|Function, (intptr_t)jsDOMImplementationPrototypeFunctionCreateCSSStyleSheet, (intptr_t)2 },
    { "createHTMLDocument", DontDelete|Function, (intptr_t)jsDOMImplementationPrototypeFunctionCreateHTMLDocument, (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static const HashTable JSDOMImplementationPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 127, JSDOMImplementationPrototypeTableValues, 0 };
#else
    { 17, 15, JSDOMImplementationPrototypeTableValues, 0 };
#endif

const ClassInfo JSDOMImplementationPrototype::s_info = { "DOMImplementationPrototype", 0, &JSDOMImplementationPrototypeTable, 0 };

JSObject* JSDOMImplementationPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSDOMImplementation>(exec, globalObject);
}

bool JSDOMImplementationPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSDOMImplementationPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSDOMImplementation::s_info = { "DOMImplementation", 0, &JSDOMImplementationTable, 0 };

JSDOMImplementation::JSDOMImplementation(PassRefPtr<Structure> structure, PassRefPtr<DOMImplementation> impl)
    : DOMObject(structure)
    , m_impl(impl)
{
}

JSDOMImplementation::~JSDOMImplementation()
{
    forgetDOMObject(*Heap::heap(this)->globalData(), m_impl.get());
}

JSObject* JSDOMImplementation::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSDOMImplementationPrototype(JSDOMImplementationPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSDOMImplementation::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSDOMImplementation, Base>(exec, &JSDOMImplementationTable, this, propertyName, slot);
}

JSValue jsDOMImplementationConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSDOMImplementation*>(asObject(slot.slotBase()))->getConstructor(exec);
}
JSValue JSDOMImplementation::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSDOMImplementationConstructor>(exec);
}

JSValue JSC_HOST_CALL jsDOMImplementationPrototypeFunctionHasFeature(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSDOMImplementation::s_info))
        return throwError(exec, TypeError);
    JSDOMImplementation* castedThisObj = static_cast<JSDOMImplementation*>(asObject(thisValue));
    DOMImplementation* imp = static_cast<DOMImplementation*>(castedThisObj->impl());
    const UString& feature = args.at(0).toString(exec);
    const UString& version = valueToStringWithNullCheck(exec, args.at(1));


    JSC::JSValue result = jsBoolean(imp->hasFeature(feature, version));
    return result;
}

JSValue JSC_HOST_CALL jsDOMImplementationPrototypeFunctionCreateDocumentType(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSDOMImplementation::s_info))
        return throwError(exec, TypeError);
    JSDOMImplementation* castedThisObj = static_cast<JSDOMImplementation*>(asObject(thisValue));
    DOMImplementation* imp = static_cast<DOMImplementation*>(castedThisObj->impl());
    ExceptionCode ec = 0;
    const UString& qualifiedName = valueToStringWithUndefinedOrNullCheck(exec, args.at(0));
    const UString& publicId = valueToStringWithUndefinedOrNullCheck(exec, args.at(1));
    const UString& systemId = valueToStringWithUndefinedOrNullCheck(exec, args.at(2));


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->createDocumentType(qualifiedName, publicId, systemId, ec)));
    setDOMException(exec, ec);
    return result;
}

JSValue JSC_HOST_CALL jsDOMImplementationPrototypeFunctionCreateDocument(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSDOMImplementation::s_info))
        return throwError(exec, TypeError);
    JSDOMImplementation* castedThisObj = static_cast<JSDOMImplementation*>(asObject(thisValue));
    DOMImplementation* imp = static_cast<DOMImplementation*>(castedThisObj->impl());
    ExceptionCode ec = 0;
    const UString& namespaceURI = valueToStringWithNullCheck(exec, args.at(0));
    const UString& qualifiedName = valueToStringWithNullCheck(exec, args.at(1));
    DocumentType* doctype = toDocumentType(args.at(2));


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->createDocument(namespaceURI, qualifiedName, doctype, ec)));
    setDOMException(exec, ec);
    return result;
}

JSValue JSC_HOST_CALL jsDOMImplementationPrototypeFunctionCreateCSSStyleSheet(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSDOMImplementation::s_info))
        return throwError(exec, TypeError);
    JSDOMImplementation* castedThisObj = static_cast<JSDOMImplementation*>(asObject(thisValue));
    DOMImplementation* imp = static_cast<DOMImplementation*>(castedThisObj->impl());
    ExceptionCode ec = 0;
    const UString& title = args.at(0).toString(exec);
    const UString& media = args.at(1).toString(exec);


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->createCSSStyleSheet(title, media, ec)));
    setDOMException(exec, ec);
    return result;
}

JSValue JSC_HOST_CALL jsDOMImplementationPrototypeFunctionCreateHTMLDocument(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSDOMImplementation::s_info))
        return throwError(exec, TypeError);
    JSDOMImplementation* castedThisObj = static_cast<JSDOMImplementation*>(asObject(thisValue));
    DOMImplementation* imp = static_cast<DOMImplementation*>(castedThisObj->impl());
    const UString& title = args.at(0).toString(exec);


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->createHTMLDocument(title)));
    return result;
}

JSC::JSValue toJS(JSC::ExecState* exec, DOMImplementation* object)
{
    return getDOMObjectWrapper<JSDOMImplementation>(exec, object);
}
DOMImplementation* toDOMImplementation(JSC::JSValue value)
{
    return value.isObject(&JSDOMImplementation::s_info) ? static_cast<JSDOMImplementation*>(asObject(value))->impl() : 0;
}

}
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

#include "JSWebKitCSSMatrix.h"

#include <wtf/GetPtr.h>

#include "JSWebKitCSSMatrix.h"
#include "KURL.h"
#include "WebKitCSSMatrix.h"

#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>
#include <runtime/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSWebKitCSSMatrix);

/* Hash table */

static const HashTableValue JSWebKitCSSMatrixTableValues[23] =
{
    { "a", DontDelete, (intptr_t)jsWebKitCSSMatrixA, (intptr_t)setJSWebKitCSSMatrixA },
    { "b", DontDelete, (intptr_t)jsWebKitCSSMatrixB, (intptr_t)setJSWebKitCSSMatrixB },
    { "c", DontDelete, (intptr_t)jsWebKitCSSMatrixC, (intptr_t)setJSWebKitCSSMatrixC },
    { "d", DontDelete, (intptr_t)jsWebKitCSSMatrixD, (intptr_t)setJSWebKitCSSMatrixD },
    { "e", DontDelete, (intptr_t)jsWebKitCSSMatrixE, (intptr_t)setJSWebKitCSSMatrixE },
    { "f", DontDelete, (intptr_t)jsWebKitCSSMatrixF, (intptr_t)setJSWebKitCSSMatrixF },
    { "m11", DontDelete, (intptr_t)jsWebKitCSSMatrixM11, (intptr_t)setJSWebKitCSSMatrixM11 },
    { "m12", DontDelete, (intptr_t)jsWebKitCSSMatrixM12, (intptr_t)setJSWebKitCSSMatrixM12 },
    { "m13", DontDelete, (intptr_t)jsWebKitCSSMatrixM13, (intptr_t)setJSWebKitCSSMatrixM13 },
    { "m14", DontDelete, (intptr_t)jsWebKitCSSMatrixM14, (intptr_t)setJSWebKitCSSMatrixM14 },
    { "m21", DontDelete, (intptr_t)jsWebKitCSSMatrixM21, (intptr_t)setJSWebKitCSSMatrixM21 },
    { "m22", DontDelete, (intptr_t)jsWebKitCSSMatrixM22, (intptr_t)setJSWebKitCSSMatrixM22 },
    { "m23", DontDelete, (intptr_t)jsWebKitCSSMatrixM23, (intptr_t)setJSWebKitCSSMatrixM23 },
    { "m24", DontDelete, (intptr_t)jsWebKitCSSMatrixM24, (intptr_t)setJSWebKitCSSMatrixM24 },
    { "m31", DontDelete, (intptr_t)jsWebKitCSSMatrixM31, (intptr_t)setJSWebKitCSSMatrixM31 },
    { "m32", DontDelete, (intptr_t)jsWebKitCSSMatrixM32, (intptr_t)setJSWebKitCSSMatrixM32 },
    { "m33", DontDelete, (intptr_t)jsWebKitCSSMatrixM33, (intptr_t)setJSWebKitCSSMatrixM33 },
    { "m34", DontDelete, (intptr_t)jsWebKitCSSMatrixM34, (intptr_t)setJSWebKitCSSMatrixM34 },
    { "m41", DontDelete, (intptr_t)jsWebKitCSSMatrixM41, (intptr_t)setJSWebKitCSSMatrixM41 },
    { "m42", DontDelete, (intptr_t)jsWebKitCSSMatrixM42, (intptr_t)setJSWebKitCSSMatrixM42 },
    { "m43", DontDelete, (intptr_t)jsWebKitCSSMatrixM43, (intptr_t)setJSWebKitCSSMatrixM43 },
    { "m44", DontDelete, (intptr_t)jsWebKitCSSMatrixM44, (intptr_t)setJSWebKitCSSMatrixM44 },
    { 0, 0, 0, 0 }
};

static const HashTable JSWebKitCSSMatrixTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 255, JSWebKitCSSMatrixTableValues, 0 };
#else
    { 65, 63, JSWebKitCSSMatrixTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSWebKitCSSMatrixPrototypeTableValues[9] =
{
    { "setMatrixValue", DontDelete|Function, (intptr_t)jsWebKitCSSMatrixPrototypeFunctionSetMatrixValue, (intptr_t)1 },
    { "multiply", DontDelete|Function, (intptr_t)jsWebKitCSSMatrixPrototypeFunctionMultiply, (intptr_t)1 },
    { "inverse", DontDelete|Function, (intptr_t)jsWebKitCSSMatrixPrototypeFunctionInverse, (intptr_t)0 },
    { "translate", DontDelete|Function, (intptr_t)jsWebKitCSSMatrixPrototypeFunctionTranslate, (intptr_t)3 },
    { "scale", DontDelete|Function, (intptr_t)jsWebKitCSSMatrixPrototypeFunctionScale, (intptr_t)3 },
    { "rotate", DontDelete|Function, (intptr_t)jsWebKitCSSMatrixPrototypeFunctionRotate, (intptr_t)3 },
    { "rotateAxisAngle", DontDelete|Function, (intptr_t)jsWebKitCSSMatrixPrototypeFunctionRotateAxisAngle, (intptr_t)4 },
    { "toString", DontDelete|DontEnum|Function, (intptr_t)jsWebKitCSSMatrixPrototypeFunctionToString, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSWebKitCSSMatrixPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 63, JSWebKitCSSMatrixPrototypeTableValues, 0 };
#else
    { 17, 15, JSWebKitCSSMatrixPrototypeTableValues, 0 };
#endif

const ClassInfo JSWebKitCSSMatrixPrototype::s_info = { "WebKitCSSMatrixPrototype", 0, &JSWebKitCSSMatrixPrototypeTable, 0 };

JSObject* JSWebKitCSSMatrixPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSWebKitCSSMatrix>(exec, globalObject);
}

bool JSWebKitCSSMatrixPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSWebKitCSSMatrixPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSWebKitCSSMatrix::s_info = { "WebKitCSSMatrix", 0, &JSWebKitCSSMatrixTable, 0 };

JSWebKitCSSMatrix::JSWebKitCSSMatrix(PassRefPtr<Structure> structure, PassRefPtr<WebKitCSSMatrix> impl)
    : DOMObject(structure)
    , m_impl(impl)
{
}

JSWebKitCSSMatrix::~JSWebKitCSSMatrix()
{
    forgetDOMObject(*Heap::heap(this)->globalData(), m_impl.get());
}

JSObject* JSWebKitCSSMatrix::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSWebKitCSSMatrixPrototype(JSWebKitCSSMatrixPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSWebKitCSSMatrix::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSWebKitCSSMatrix, Base>(exec, &JSWebKitCSSMatrixTable, this, propertyName, slot);
}

JSValue jsWebKitCSSMatrixA(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->a());
}

JSValue jsWebKitCSSMatrixB(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->b());
}

JSValue jsWebKitCSSMatrixC(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->c());
}

JSValue jsWebKitCSSMatrixD(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->d());
}

JSValue jsWebKitCSSMatrixE(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->e());
}

JSValue jsWebKitCSSMatrixF(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->f());
}

JSValue jsWebKitCSSMatrixM11(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->m11());
}

JSValue jsWebKitCSSMatrixM12(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->m12());
}

JSValue jsWebKitCSSMatrixM13(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->m13());
}

JSValue jsWebKitCSSMatrixM14(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->m14());
}

JSValue jsWebKitCSSMatrixM21(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->m21());
}

JSValue jsWebKitCSSMatrixM22(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->m22());
}

JSValue jsWebKitCSSMatrixM23(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->m23());
}

JSValue jsWebKitCSSMatrixM24(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->m24());
}

JSValue jsWebKitCSSMatrixM31(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->m31());
}

JSValue jsWebKitCSSMatrixM32(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->m32());
}

JSValue jsWebKitCSSMatrixM33(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->m33());
}

JSValue jsWebKitCSSMatrixM34(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->m34());
}

JSValue jsWebKitCSSMatrixM41(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->m41());
}

JSValue jsWebKitCSSMatrixM42(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->m42());
}

JSValue jsWebKitCSSMatrixM43(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->m43());
}

JSValue jsWebKitCSSMatrixM44(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->m44());
}

void JSWebKitCSSMatrix::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSWebKitCSSMatrix, Base>(exec, propertyName, value, &JSWebKitCSSMatrixTable, this, slot);
}

void setJSWebKitCSSMatrixA(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setA(value.toNumber(exec));
}

void setJSWebKitCSSMatrixB(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setB(value.toNumber(exec));
}

void setJSWebKitCSSMatrixC(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setC(value.toNumber(exec));
}

void setJSWebKitCSSMatrixD(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setD(value.toNumber(exec));
}

void setJSWebKitCSSMatrixE(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setE(value.toNumber(exec));
}

void setJSWebKitCSSMatrixF(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setF(value.toNumber(exec));
}

void setJSWebKitCSSMatrixM11(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setM11(value.toNumber(exec));
}

void setJSWebKitCSSMatrixM12(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setM12(value.toNumber(exec));
}

void setJSWebKitCSSMatrixM13(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setM13(value.toNumber(exec));
}

void setJSWebKitCSSMatrixM14(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setM14(value.toNumber(exec));
}

void setJSWebKitCSSMatrixM21(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setM21(value.toNumber(exec));
}

void setJSWebKitCSSMatrixM22(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setM22(value.toNumber(exec));
}

void setJSWebKitCSSMatrixM23(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setM23(value.toNumber(exec));
}

void setJSWebKitCSSMatrixM24(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setM24(value.toNumber(exec));
}

void setJSWebKitCSSMatrixM31(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setM31(value.toNumber(exec));
}

void setJSWebKitCSSMatrixM32(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setM32(value.toNumber(exec));
}

void setJSWebKitCSSMatrixM33(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setM33(value.toNumber(exec));
}

void setJSWebKitCSSMatrixM34(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setM34(value.toNumber(exec));
}

void setJSWebKitCSSMatrixM41(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setM41(value.toNumber(exec));
}

void setJSWebKitCSSMatrixM42(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setM42(value.toNumber(exec));
}

void setJSWebKitCSSMatrixM43(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setM43(value.toNumber(exec));
}

void setJSWebKitCSSMatrixM44(ExecState* exec, JSObject* thisObject, JSValue value)
{
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(static_cast<JSWebKitCSSMatrix*>(thisObject)->impl());
    imp->setM44(value.toNumber(exec));
}

JSValue JSC_HOST_CALL jsWebKitCSSMatrixPrototypeFunctionSetMatrixValue(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSWebKitCSSMatrix::s_info))
        return throwError(exec, TypeError);
    JSWebKitCSSMatrix* castedThisObj = static_cast<JSWebKitCSSMatrix*>(asObject(thisValue));
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(castedThisObj->impl());
    ExceptionCode ec = 0;
    const UString& string = args.at(0).toString(exec);

    imp->setMatrixValue(string, ec);
    setDOMException(exec, ec);
    return jsUndefined();
}

JSValue JSC_HOST_CALL jsWebKitCSSMatrixPrototypeFunctionMultiply(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSWebKitCSSMatrix::s_info))
        return throwError(exec, TypeError);
    JSWebKitCSSMatrix* castedThisObj = static_cast<JSWebKitCSSMatrix*>(asObject(thisValue));
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(castedThisObj->impl());
    WebKitCSSMatrix* secondMatrix = toWebKitCSSMatrix(args.at(0));


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->multiply(secondMatrix)));
    return result;
}

JSValue JSC_HOST_CALL jsWebKitCSSMatrixPrototypeFunctionInverse(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSWebKitCSSMatrix::s_info))
        return throwError(exec, TypeError);
    JSWebKitCSSMatrix* castedThisObj = static_cast<JSWebKitCSSMatrix*>(asObject(thisValue));
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(castedThisObj->impl());
    ExceptionCode ec = 0;


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->inverse(ec)));
    setDOMException(exec, ec);
    return result;
}

JSValue JSC_HOST_CALL jsWebKitCSSMatrixPrototypeFunctionTranslate(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSWebKitCSSMatrix::s_info))
        return throwError(exec, TypeError);
    JSWebKitCSSMatrix* castedThisObj = static_cast<JSWebKitCSSMatrix*>(asObject(thisValue));
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(castedThisObj->impl());
    double x = args.at(0).toNumber(exec);
    double y = args.at(1).toNumber(exec);
    double z = args.at(2).toNumber(exec);


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->translate(x, y, z)));
    return result;
}

JSValue JSC_HOST_CALL jsWebKitCSSMatrixPrototypeFunctionScale(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSWebKitCSSMatrix::s_info))
        return throwError(exec, TypeError);
    JSWebKitCSSMatrix* castedThisObj = static_cast<JSWebKitCSSMatrix*>(asObject(thisValue));
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(castedThisObj->impl());
    double scaleX = args.at(0).toNumber(exec);
    double scaleY = args.at(1).toNumber(exec);
    double scaleZ = args.at(2).toNumber(exec);


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->scale(scaleX, scaleY, scaleZ)));
    return result;
}

JSValue JSC_HOST_CALL jsWebKitCSSMatrixPrototypeFunctionRotate(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSWebKitCSSMatrix::s_info))
        return throwError(exec, TypeError);
    JSWebKitCSSMatrix* castedThisObj = static_cast<JSWebKitCSSMatrix*>(asObject(thisValue));
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(castedThisObj->impl());
    double rotX = args.at(0).toNumber(exec);
    double rotY = args.at(1).toNumber(exec);
    double rotZ = args.at(2).toNumber(exec);


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->rotate(rotX, rotY, rotZ)));
    return result;
}

JSValue JSC_HOST_CALL jsWebKitCSSMatrixPrototypeFunctionRotateAxisAngle(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSWebKitCSSMatrix::s_info))
        return throwError(exec, TypeError);
    JSWebKitCSSMatrix* castedThisObj = static_cast<JSWebKitCSSMatrix*>(asObject(thisValue));
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(castedThisObj->impl());
    double x = args.at(0).toNumber(exec);
    double y = args.at(1).toNumber(exec);
    double z = args.at(2).toNumber(exec);
    double angle = args.at(3).toNumber(exec);


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->rotateAxisAngle(x, y, z, angle)));
    return result;
}

JSValue JSC_HOST_CALL jsWebKitCSSMatrixPrototypeFunctionToString(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSWebKitCSSMatrix::s_info))
        return throwError(exec, TypeError);
    JSWebKitCSSMatrix* castedThisObj = static_cast<JSWebKitCSSMatrix*>(asObject(thisValue));
    WebKitCSSMatrix* imp = static_cast<WebKitCSSMatrix*>(castedThisObj->impl());


    JSC::JSValue result = jsString(exec, imp->toString());
    return result;
}

JSC::JSValue toJS(JSC::ExecState* exec, WebKitCSSMatrix* object)
{
    return getDOMObjectWrapper<JSWebKitCSSMatrix>(exec, object);
}
WebKitCSSMatrix* toWebKitCSSMatrix(JSC::JSValue value)
{
    return value.isObject(&JSWebKitCSSMatrix::s_info) ? static_cast<JSWebKitCSSMatrix*>(asObject(value))->impl() : 0;
}

}

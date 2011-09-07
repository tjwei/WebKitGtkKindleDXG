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


#if ENABLE(SVG) && ENABLE(SVG_FILTERS)

#include "SVGElement.h"
#include "JSSVGFESpecularLightingElement.h"

#include <wtf/GetPtr.h>

#include "CSSMutableStyleDeclaration.h"
#include "CSSStyleDeclaration.h"
#include "CSSValue.h"
#include "JSCSSStyleDeclaration.h"
#include "JSCSSValue.h"
#include "JSSVGAnimatedLength.h"
#include "JSSVGAnimatedNumber.h"
#include "JSSVGAnimatedString.h"
#include "SVGFESpecularLightingElement.h"

#include <runtime/Error.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGFESpecularLightingElement);

/* Hash table */

static const HashTableValue JSSVGFESpecularLightingElementTableValues[12] =
{
    { "in1", DontDelete|ReadOnly, (intptr_t)jsSVGFESpecularLightingElementIn1, (intptr_t)0 },
    { "surfaceScale", DontDelete|ReadOnly, (intptr_t)jsSVGFESpecularLightingElementSurfaceScale, (intptr_t)0 },
    { "specularConstant", DontDelete|ReadOnly, (intptr_t)jsSVGFESpecularLightingElementSpecularConstant, (intptr_t)0 },
    { "specularExponent", DontDelete|ReadOnly, (intptr_t)jsSVGFESpecularLightingElementSpecularExponent, (intptr_t)0 },
    { "x", DontDelete|ReadOnly, (intptr_t)jsSVGFESpecularLightingElementX, (intptr_t)0 },
    { "y", DontDelete|ReadOnly, (intptr_t)jsSVGFESpecularLightingElementY, (intptr_t)0 },
    { "width", DontDelete|ReadOnly, (intptr_t)jsSVGFESpecularLightingElementWidth, (intptr_t)0 },
    { "height", DontDelete|ReadOnly, (intptr_t)jsSVGFESpecularLightingElementHeight, (intptr_t)0 },
    { "result", DontDelete|ReadOnly, (intptr_t)jsSVGFESpecularLightingElementResult, (intptr_t)0 },
    { "className", DontDelete|ReadOnly, (intptr_t)jsSVGFESpecularLightingElementClassName, (intptr_t)0 },
    { "style", DontDelete|ReadOnly, (intptr_t)jsSVGFESpecularLightingElementStyle, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGFESpecularLightingElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 1023, JSSVGFESpecularLightingElementTableValues, 0 };
#else
    { 36, 31, JSSVGFESpecularLightingElementTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSSVGFESpecularLightingElementPrototypeTableValues[2] =
{
    { "getPresentationAttribute", DontDelete|Function, (intptr_t)jsSVGFESpecularLightingElementPrototypeFunctionGetPresentationAttribute, (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGFESpecularLightingElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGFESpecularLightingElementPrototypeTableValues, 0 };
#else
    { 2, 1, JSSVGFESpecularLightingElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGFESpecularLightingElementPrototype::s_info = { "SVGFESpecularLightingElementPrototype", 0, &JSSVGFESpecularLightingElementPrototypeTable, 0 };

JSObject* JSSVGFESpecularLightingElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGFESpecularLightingElement>(exec, globalObject);
}

bool JSSVGFESpecularLightingElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSSVGFESpecularLightingElementPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSSVGFESpecularLightingElement::s_info = { "SVGFESpecularLightingElement", &JSSVGElement::s_info, &JSSVGFESpecularLightingElementTable, 0 };

JSSVGFESpecularLightingElement::JSSVGFESpecularLightingElement(PassRefPtr<Structure> structure, PassRefPtr<SVGFESpecularLightingElement> impl)
    : JSSVGElement(structure, impl)
{
}

JSObject* JSSVGFESpecularLightingElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGFESpecularLightingElementPrototype(JSSVGFESpecularLightingElementPrototype::createStructure(JSSVGElementPrototype::self(exec, globalObject)));
}

bool JSSVGFESpecularLightingElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGFESpecularLightingElement, Base>(exec, &JSSVGFESpecularLightingElementTable, this, propertyName, slot);
}

JSValue jsSVGFESpecularLightingElementIn1(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGFESpecularLightingElement* imp = static_cast<SVGFESpecularLightingElement*>(static_cast<JSSVGFESpecularLightingElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedString> obj = imp->in1Animated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGFESpecularLightingElementSurfaceScale(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGFESpecularLightingElement* imp = static_cast<SVGFESpecularLightingElement*>(static_cast<JSSVGFESpecularLightingElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedNumber> obj = imp->surfaceScaleAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGFESpecularLightingElementSpecularConstant(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGFESpecularLightingElement* imp = static_cast<SVGFESpecularLightingElement*>(static_cast<JSSVGFESpecularLightingElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedNumber> obj = imp->specularConstantAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGFESpecularLightingElementSpecularExponent(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGFESpecularLightingElement* imp = static_cast<SVGFESpecularLightingElement*>(static_cast<JSSVGFESpecularLightingElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedNumber> obj = imp->specularExponentAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGFESpecularLightingElementX(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGFESpecularLightingElement* imp = static_cast<SVGFESpecularLightingElement*>(static_cast<JSSVGFESpecularLightingElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedLength> obj = imp->xAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGFESpecularLightingElementY(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGFESpecularLightingElement* imp = static_cast<SVGFESpecularLightingElement*>(static_cast<JSSVGFESpecularLightingElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedLength> obj = imp->yAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGFESpecularLightingElementWidth(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGFESpecularLightingElement* imp = static_cast<SVGFESpecularLightingElement*>(static_cast<JSSVGFESpecularLightingElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedLength> obj = imp->widthAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGFESpecularLightingElementHeight(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGFESpecularLightingElement* imp = static_cast<SVGFESpecularLightingElement*>(static_cast<JSSVGFESpecularLightingElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedLength> obj = imp->heightAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGFESpecularLightingElementResult(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGFESpecularLightingElement* imp = static_cast<SVGFESpecularLightingElement*>(static_cast<JSSVGFESpecularLightingElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedString> obj = imp->resultAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGFESpecularLightingElementClassName(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGFESpecularLightingElement* imp = static_cast<SVGFESpecularLightingElement*>(static_cast<JSSVGFESpecularLightingElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedString> obj = imp->classNameAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGFESpecularLightingElementStyle(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGFESpecularLightingElement* imp = static_cast<SVGFESpecularLightingElement*>(static_cast<JSSVGFESpecularLightingElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->style()));
}

JSValue JSC_HOST_CALL jsSVGFESpecularLightingElementPrototypeFunctionGetPresentationAttribute(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSSVGFESpecularLightingElement::s_info))
        return throwError(exec, TypeError);
    JSSVGFESpecularLightingElement* castedThisObj = static_cast<JSSVGFESpecularLightingElement*>(asObject(thisValue));
    SVGFESpecularLightingElement* imp = static_cast<SVGFESpecularLightingElement*>(castedThisObj->impl());
    const UString& name = args.at(0).toString(exec);


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->getPresentationAttribute(name)));
    return result;
}


}

#endif // ENABLE(SVG) && ENABLE(SVG_FILTERS)

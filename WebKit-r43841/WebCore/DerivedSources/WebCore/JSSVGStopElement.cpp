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


#if ENABLE(SVG)

#include "SVGElement.h"
#include "JSSVGStopElement.h"

#include <wtf/GetPtr.h>

#include "CSSMutableStyleDeclaration.h"
#include "CSSStyleDeclaration.h"
#include "CSSValue.h"
#include "JSCSSStyleDeclaration.h"
#include "JSCSSValue.h"
#include "JSSVGAnimatedNumber.h"
#include "JSSVGAnimatedString.h"
#include "SVGStopElement.h"

#include <runtime/Error.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGStopElement);

/* Hash table */

static const HashTableValue JSSVGStopElementTableValues[4] =
{
    { "offset", DontDelete|ReadOnly, (intptr_t)jsSVGStopElementOffset, (intptr_t)0 },
    { "className", DontDelete|ReadOnly, (intptr_t)jsSVGStopElementClassName, (intptr_t)0 },
    { "style", DontDelete|ReadOnly, (intptr_t)jsSVGStopElementStyle, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGStopElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 7, JSSVGStopElementTableValues, 0 };
#else
    { 8, 7, JSSVGStopElementTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSSVGStopElementPrototypeTableValues[2] =
{
    { "getPresentationAttribute", DontDelete|Function, (intptr_t)jsSVGStopElementPrototypeFunctionGetPresentationAttribute, (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGStopElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGStopElementPrototypeTableValues, 0 };
#else
    { 2, 1, JSSVGStopElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGStopElementPrototype::s_info = { "SVGStopElementPrototype", 0, &JSSVGStopElementPrototypeTable, 0 };

JSObject* JSSVGStopElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGStopElement>(exec, globalObject);
}

bool JSSVGStopElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSSVGStopElementPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSSVGStopElement::s_info = { "SVGStopElement", &JSSVGElement::s_info, &JSSVGStopElementTable, 0 };

JSSVGStopElement::JSSVGStopElement(PassRefPtr<Structure> structure, PassRefPtr<SVGStopElement> impl)
    : JSSVGElement(structure, impl)
{
}

JSObject* JSSVGStopElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGStopElementPrototype(JSSVGStopElementPrototype::createStructure(JSSVGElementPrototype::self(exec, globalObject)));
}

bool JSSVGStopElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGStopElement, Base>(exec, &JSSVGStopElementTable, this, propertyName, slot);
}

JSValue jsSVGStopElementOffset(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGStopElement* imp = static_cast<SVGStopElement*>(static_cast<JSSVGStopElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedNumber> obj = imp->offsetAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGStopElementClassName(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGStopElement* imp = static_cast<SVGStopElement*>(static_cast<JSSVGStopElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedString> obj = imp->classNameAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGStopElementStyle(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGStopElement* imp = static_cast<SVGStopElement*>(static_cast<JSSVGStopElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->style()));
}

JSValue JSC_HOST_CALL jsSVGStopElementPrototypeFunctionGetPresentationAttribute(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSSVGStopElement::s_info))
        return throwError(exec, TypeError);
    JSSVGStopElement* castedThisObj = static_cast<JSSVGStopElement*>(asObject(thisValue));
    SVGStopElement* imp = static_cast<SVGStopElement*>(castedThisObj->impl());
    const UString& name = args.at(0).toString(exec);


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->getPresentationAttribute(name)));
    return result;
}


}

#endif // ENABLE(SVG)

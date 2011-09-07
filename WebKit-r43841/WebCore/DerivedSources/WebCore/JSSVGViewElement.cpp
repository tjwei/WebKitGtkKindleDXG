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
#include "JSSVGViewElement.h"

#include <wtf/GetPtr.h>

#include "JSSVGAnimatedBoolean.h"
#include "JSSVGAnimatedPreserveAspectRatio.h"
#include "JSSVGAnimatedRect.h"
#include "JSSVGStringList.h"
#include "SVGStringList.h"
#include "SVGViewElement.h"

#include <runtime/JSNumberCell.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGViewElement);

/* Hash table */

static const HashTableValue JSSVGViewElementTableValues[6] =
{
    { "viewTarget", DontDelete|ReadOnly, (intptr_t)jsSVGViewElementViewTarget, (intptr_t)0 },
    { "externalResourcesRequired", DontDelete|ReadOnly, (intptr_t)jsSVGViewElementExternalResourcesRequired, (intptr_t)0 },
    { "viewBox", DontDelete|ReadOnly, (intptr_t)jsSVGViewElementViewBox, (intptr_t)0 },
    { "preserveAspectRatio", DontDelete|ReadOnly, (intptr_t)jsSVGViewElementPreserveAspectRatio, (intptr_t)0 },
    { "zoomAndPan", DontDelete, (intptr_t)jsSVGViewElementZoomAndPan, (intptr_t)setJSSVGViewElementZoomAndPan },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGViewElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSSVGViewElementTableValues, 0 };
#else
    { 16, 15, JSSVGViewElementTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSSVGViewElementPrototypeTableValues[4] =
{
    { "SVG_ZOOMANDPAN_UNKNOWN", DontDelete|ReadOnly, (intptr_t)jsSVGViewElementSVG_ZOOMANDPAN_UNKNOWN, (intptr_t)0 },
    { "SVG_ZOOMANDPAN_DISABLE", DontDelete|ReadOnly, (intptr_t)jsSVGViewElementSVG_ZOOMANDPAN_DISABLE, (intptr_t)0 },
    { "SVG_ZOOMANDPAN_MAGNIFY", DontDelete|ReadOnly, (intptr_t)jsSVGViewElementSVG_ZOOMANDPAN_MAGNIFY, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGViewElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 31, JSSVGViewElementPrototypeTableValues, 0 };
#else
    { 9, 7, JSSVGViewElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGViewElementPrototype::s_info = { "SVGViewElementPrototype", 0, &JSSVGViewElementPrototypeTable, 0 };

JSObject* JSSVGViewElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGViewElement>(exec, globalObject);
}

bool JSSVGViewElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGViewElementPrototype, JSObject>(exec, &JSSVGViewElementPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSSVGViewElement::s_info = { "SVGViewElement", &JSSVGElement::s_info, &JSSVGViewElementTable, 0 };

JSSVGViewElement::JSSVGViewElement(PassRefPtr<Structure> structure, PassRefPtr<SVGViewElement> impl)
    : JSSVGElement(structure, impl)
{
}

JSObject* JSSVGViewElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGViewElementPrototype(JSSVGViewElementPrototype::createStructure(JSSVGElementPrototype::self(exec, globalObject)));
}

bool JSSVGViewElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGViewElement, Base>(exec, &JSSVGViewElementTable, this, propertyName, slot);
}

JSValue jsSVGViewElementViewTarget(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGViewElement* imp = static_cast<SVGViewElement*>(static_cast<JSSVGViewElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->viewTarget()), imp);
}

JSValue jsSVGViewElementExternalResourcesRequired(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGViewElement* imp = static_cast<SVGViewElement*>(static_cast<JSSVGViewElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedBoolean> obj = imp->externalResourcesRequiredAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGViewElementViewBox(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGViewElement* imp = static_cast<SVGViewElement*>(static_cast<JSSVGViewElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedRect> obj = imp->viewBoxAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGViewElementPreserveAspectRatio(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGViewElement* imp = static_cast<SVGViewElement*>(static_cast<JSSVGViewElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedPreserveAspectRatio> obj = imp->preserveAspectRatioAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGViewElementZoomAndPan(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGViewElement* imp = static_cast<SVGViewElement*>(static_cast<JSSVGViewElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->zoomAndPan());
}

void JSSVGViewElement::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSSVGViewElement, Base>(exec, propertyName, value, &JSSVGViewElementTable, this, slot);
}

void setJSSVGViewElementZoomAndPan(ExecState* exec, JSObject* thisObject, JSValue value)
{
    SVGViewElement* imp = static_cast<SVGViewElement*>(static_cast<JSSVGViewElement*>(thisObject)->impl());
    imp->setZoomAndPan(value.toInt32(exec));
}

// Constant getters

JSValue jsSVGViewElementSVG_ZOOMANDPAN_UNKNOWN(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(0));
}

JSValue jsSVGViewElementSVG_ZOOMANDPAN_DISABLE(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(1));
}

JSValue jsSVGViewElementSVG_ZOOMANDPAN_MAGNIFY(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(2));
}


}

#endif // ENABLE(SVG)
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
#include "JSSVGAnimatedBoolean.h"

#include <wtf/GetPtr.h>



using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGAnimatedBoolean);

/* Hash table */

static const HashTableValue JSSVGAnimatedBooleanTableValues[3] =
{
    { "baseVal", DontDelete, (intptr_t)jsSVGAnimatedBooleanBaseVal, (intptr_t)setJSSVGAnimatedBooleanBaseVal },
    { "animVal", DontDelete|ReadOnly, (intptr_t)jsSVGAnimatedBooleanAnimVal, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGAnimatedBooleanTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 1, JSSVGAnimatedBooleanTableValues, 0 };
#else
    { 4, 3, JSSVGAnimatedBooleanTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSSVGAnimatedBooleanPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGAnimatedBooleanPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGAnimatedBooleanPrototypeTableValues, 0 };
#else
    { 1, 0, JSSVGAnimatedBooleanPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGAnimatedBooleanPrototype::s_info = { "SVGAnimatedBooleanPrototype", 0, &JSSVGAnimatedBooleanPrototypeTable, 0 };

JSObject* JSSVGAnimatedBooleanPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGAnimatedBoolean>(exec, globalObject);
}

const ClassInfo JSSVGAnimatedBoolean::s_info = { "SVGAnimatedBoolean", 0, &JSSVGAnimatedBooleanTable, 0 };

JSSVGAnimatedBoolean::JSSVGAnimatedBoolean(PassRefPtr<Structure> structure, PassRefPtr<SVGAnimatedBoolean> impl, SVGElement* context)
    : DOMObject(structure)
    , m_context(context)
    , m_impl(impl)
{
}

JSSVGAnimatedBoolean::~JSSVGAnimatedBoolean()
{
    forgetDOMObject(*Heap::heap(this)->globalData(), m_impl.get());
}

JSObject* JSSVGAnimatedBoolean::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGAnimatedBooleanPrototype(JSSVGAnimatedBooleanPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSSVGAnimatedBoolean::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGAnimatedBoolean, Base>(exec, &JSSVGAnimatedBooleanTable, this, propertyName, slot);
}

JSValue jsSVGAnimatedBooleanBaseVal(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGAnimatedBoolean* imp = static_cast<SVGAnimatedBoolean*>(static_cast<JSSVGAnimatedBoolean*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->baseVal());
}

JSValue jsSVGAnimatedBooleanAnimVal(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGAnimatedBoolean* imp = static_cast<SVGAnimatedBoolean*>(static_cast<JSSVGAnimatedBoolean*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->animVal());
}

void JSSVGAnimatedBoolean::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSSVGAnimatedBoolean, Base>(exec, propertyName, value, &JSSVGAnimatedBooleanTable, this, slot);
}

void setJSSVGAnimatedBooleanBaseVal(ExecState* exec, JSObject* thisObject, JSValue value)
{
    SVGAnimatedBoolean* imp = static_cast<SVGAnimatedBoolean*>(static_cast<JSSVGAnimatedBoolean*>(thisObject)->impl());
    imp->setBaseVal(value.toBoolean(exec));
    if (static_cast<JSSVGAnimatedBoolean*>(thisObject)->context())
        static_cast<JSSVGAnimatedBoolean*>(thisObject)->context()->svgAttributeChanged(static_cast<JSSVGAnimatedBoolean*>(thisObject)->impl()->associatedAttributeName());
}

JSC::JSValue toJS(JSC::ExecState* exec, SVGAnimatedBoolean* object, SVGElement* context)
{
    return getDOMObjectWrapper<JSSVGAnimatedBoolean>(exec, object, context);
}
SVGAnimatedBoolean* toSVGAnimatedBoolean(JSC::JSValue value)
{
    return value.isObject(&JSSVGAnimatedBoolean::s_info) ? static_cast<JSSVGAnimatedBoolean*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(SVG)

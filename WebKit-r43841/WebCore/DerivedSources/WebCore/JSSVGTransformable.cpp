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
#include "JSSVGTransformable.h"

#include <wtf/GetPtr.h>

#include "JSSVGAnimatedTransformList.h"
#include "SVGTransformable.h"


using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGTransformable);

/* Hash table */

static const HashTableValue JSSVGTransformableTableValues[2] =
{
    { "transform", DontDelete|ReadOnly, (intptr_t)jsSVGTransformableTransform, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGTransformableTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGTransformableTableValues, 0 };
#else
    { 2, 1, JSSVGTransformableTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSSVGTransformablePrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGTransformablePrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGTransformablePrototypeTableValues, 0 };
#else
    { 1, 0, JSSVGTransformablePrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGTransformablePrototype::s_info = { "SVGTransformablePrototype", 0, &JSSVGTransformablePrototypeTable, 0 };

JSObject* JSSVGTransformablePrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGTransformable>(exec, globalObject);
}

const ClassInfo JSSVGTransformable::s_info = { "SVGTransformable", &JSSVGLocatable::s_info, &JSSVGTransformableTable, 0 };

JSSVGTransformable::JSSVGTransformable(PassRefPtr<Structure> structure, PassRefPtr<SVGTransformable> impl, SVGElement* context)
    : JSSVGLocatable(structure, impl, context)
{
}

JSObject* JSSVGTransformable::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGTransformablePrototype(JSSVGTransformablePrototype::createStructure(JSSVGLocatablePrototype::self(exec, globalObject)));
}

bool JSSVGTransformable::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGTransformable, Base>(exec, &JSSVGTransformableTable, this, propertyName, slot);
}

JSValue jsSVGTransformableTransform(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGTransformable* imp = static_cast<SVGTransformable*>(static_cast<JSSVGTransformable*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedTransformList> obj = imp->transformAnimated();
    return toJS(exec, obj.get(), imp);
}


}

#endif // ENABLE(SVG)

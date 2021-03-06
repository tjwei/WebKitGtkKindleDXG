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
#include "JSSVGLangSpace.h"

#include <wtf/GetPtr.h>

#include "KURL.h"
#include "SVGLangSpace.h"

#include <runtime/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGLangSpace);

/* Hash table */

static const HashTableValue JSSVGLangSpaceTableValues[3] =
{
    { "xmllang", DontDelete, (intptr_t)jsSVGLangSpaceXmllang, (intptr_t)setJSSVGLangSpaceXmllang },
    { "xmlspace", DontDelete, (intptr_t)jsSVGLangSpaceXmlspace, (intptr_t)setJSSVGLangSpaceXmlspace },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGLangSpaceTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSSVGLangSpaceTableValues, 0 };
#else
    { 5, 3, JSSVGLangSpaceTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSSVGLangSpacePrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGLangSpacePrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGLangSpacePrototypeTableValues, 0 };
#else
    { 1, 0, JSSVGLangSpacePrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGLangSpacePrototype::s_info = { "SVGLangSpacePrototype", 0, &JSSVGLangSpacePrototypeTable, 0 };

JSObject* JSSVGLangSpacePrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGLangSpace>(exec, globalObject);
}

const ClassInfo JSSVGLangSpace::s_info = { "SVGLangSpace", 0, &JSSVGLangSpaceTable, 0 };

JSSVGLangSpace::JSSVGLangSpace(PassRefPtr<Structure> structure, PassRefPtr<SVGLangSpace> impl, SVGElement* context)
    : DOMObject(structure)
    , m_context(context)
    , m_impl(impl)
{
}

JSSVGLangSpace::~JSSVGLangSpace()
{
    forgetDOMObject(*Heap::heap(this)->globalData(), m_impl.get());
}

JSObject* JSSVGLangSpace::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGLangSpacePrototype(JSSVGLangSpacePrototype::createStructure(globalObject->objectPrototype()));
}

bool JSSVGLangSpace::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGLangSpace, Base>(exec, &JSSVGLangSpaceTable, this, propertyName, slot);
}

JSValue jsSVGLangSpaceXmllang(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGLangSpace* imp = static_cast<SVGLangSpace*>(static_cast<JSSVGLangSpace*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->xmllang());
}

JSValue jsSVGLangSpaceXmlspace(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGLangSpace* imp = static_cast<SVGLangSpace*>(static_cast<JSSVGLangSpace*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->xmlspace());
}

void JSSVGLangSpace::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSSVGLangSpace, Base>(exec, propertyName, value, &JSSVGLangSpaceTable, this, slot);
}

void setJSSVGLangSpaceXmllang(ExecState* exec, JSObject* thisObject, JSValue value)
{
    SVGLangSpace* imp = static_cast<SVGLangSpace*>(static_cast<JSSVGLangSpace*>(thisObject)->impl());
    imp->setXmllang(value.toString(exec));
    if (static_cast<JSSVGLangSpace*>(thisObject)->context())
        static_cast<JSSVGLangSpace*>(thisObject)->context()->svgAttributeChanged(static_cast<JSSVGLangSpace*>(thisObject)->impl()->associatedAttributeName());
}

void setJSSVGLangSpaceXmlspace(ExecState* exec, JSObject* thisObject, JSValue value)
{
    SVGLangSpace* imp = static_cast<SVGLangSpace*>(static_cast<JSSVGLangSpace*>(thisObject)->impl());
    imp->setXmlspace(value.toString(exec));
    if (static_cast<JSSVGLangSpace*>(thisObject)->context())
        static_cast<JSSVGLangSpace*>(thisObject)->context()->svgAttributeChanged(static_cast<JSSVGLangSpace*>(thisObject)->impl()->associatedAttributeName());
}

JSC::JSValue toJS(JSC::ExecState* exec, SVGLangSpace* object, SVGElement* context)
{
    return getDOMObjectWrapper<JSSVGLangSpace>(exec, object, context);
}
SVGLangSpace* toSVGLangSpace(JSC::JSValue value)
{
    return value.isObject(&JSSVGLangSpace::s_info) ? static_cast<JSSVGLangSpace*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(SVG)

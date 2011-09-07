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

#include "JSCanvasGradient.h"

#include <wtf/GetPtr.h>

#include "CanvasGradient.h"
#include "PlatformString.h"

#include <runtime/Error.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSCanvasGradient);

/* Hash table for prototype */

static const HashTableValue JSCanvasGradientPrototypeTableValues[2] =
{
    { "addColorStop", DontDelete|Function, (intptr_t)jsCanvasGradientPrototypeFunctionAddColorStop, (intptr_t)2 },
    { 0, 0, 0, 0 }
};

static const HashTable JSCanvasGradientPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSCanvasGradientPrototypeTableValues, 0 };
#else
    { 2, 1, JSCanvasGradientPrototypeTableValues, 0 };
#endif

const ClassInfo JSCanvasGradientPrototype::s_info = { "CanvasGradientPrototype", 0, &JSCanvasGradientPrototypeTable, 0 };

JSObject* JSCanvasGradientPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSCanvasGradient>(exec, globalObject);
}

bool JSCanvasGradientPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSCanvasGradientPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSCanvasGradient::s_info = { "CanvasGradient", 0, 0, 0 };

JSCanvasGradient::JSCanvasGradient(PassRefPtr<Structure> structure, PassRefPtr<CanvasGradient> impl)
    : DOMObject(structure)
    , m_impl(impl)
{
}

JSCanvasGradient::~JSCanvasGradient()
{
    forgetDOMObject(*Heap::heap(this)->globalData(), m_impl.get());
}

JSObject* JSCanvasGradient::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSCanvasGradientPrototype(JSCanvasGradientPrototype::createStructure(globalObject->objectPrototype()));
}

JSValue JSC_HOST_CALL jsCanvasGradientPrototypeFunctionAddColorStop(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSCanvasGradient::s_info))
        return throwError(exec, TypeError);
    JSCanvasGradient* castedThisObj = static_cast<JSCanvasGradient*>(asObject(thisValue));
    CanvasGradient* imp = static_cast<CanvasGradient*>(castedThisObj->impl());
    ExceptionCode ec = 0;
    float offset = args.at(0).toFloat(exec);
    const UString& color = args.at(1).toString(exec);

    imp->addColorStop(offset, color, ec);
    setDOMException(exec, ec);
    return jsUndefined();
}

JSC::JSValue toJS(JSC::ExecState* exec, CanvasGradient* object)
{
    return getDOMObjectWrapper<JSCanvasGradient>(exec, object);
}
CanvasGradient* toCanvasGradient(JSC::JSValue value)
{
    return value.isObject(&JSCanvasGradient::s_info) ? static_cast<JSCanvasGradient*>(asObject(value))->impl() : 0;
}

}

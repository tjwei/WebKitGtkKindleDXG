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


#if ENABLE(WORKERS)

#include "JSWorker.h"

#include <wtf/GetPtr.h>

#include "Event.h"
#include "EventListener.h"
#include "Frame.h"
#include "JSDOMGlobalObject.h"
#include "JSEvent.h"
#include "JSEventListener.h"
#include "Worker.h"

#include <runtime/Error.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSWorker);

/* Hash table */

static const HashTableValue JSWorkerTableValues[3] =
{
    { "onerror", DontDelete, (intptr_t)jsWorkerOnerror, (intptr_t)setJSWorkerOnerror },
    { "onmessage", DontDelete, (intptr_t)jsWorkerOnmessage, (intptr_t)setJSWorkerOnmessage },
    { 0, 0, 0, 0 }
};

static const HashTable JSWorkerTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 3, JSWorkerTableValues, 0 };
#else
    { 4, 3, JSWorkerTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSWorkerPrototypeTableValues[6] =
{
    { "postMessage", DontDelete|Function, (intptr_t)jsWorkerPrototypeFunctionPostMessage, (intptr_t)1 },
    { "terminate", DontDelete|Function, (intptr_t)jsWorkerPrototypeFunctionTerminate, (intptr_t)0 },
    { "addEventListener", DontDelete|Function, (intptr_t)jsWorkerPrototypeFunctionAddEventListener, (intptr_t)3 },
    { "removeEventListener", DontDelete|Function, (intptr_t)jsWorkerPrototypeFunctionRemoveEventListener, (intptr_t)3 },
    { "dispatchEvent", DontDelete|Function, (intptr_t)jsWorkerPrototypeFunctionDispatchEvent, (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static const HashTable JSWorkerPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSWorkerPrototypeTableValues, 0 };
#else
    { 16, 15, JSWorkerPrototypeTableValues, 0 };
#endif

const ClassInfo JSWorkerPrototype::s_info = { "WorkerPrototype", 0, &JSWorkerPrototypeTable, 0 };

JSObject* JSWorkerPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSWorker>(exec, globalObject);
}

bool JSWorkerPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSWorkerPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSWorker::s_info = { "Worker", 0, &JSWorkerTable, 0 };

JSWorker::JSWorker(PassRefPtr<Structure> structure, PassRefPtr<Worker> impl)
    : DOMObject(structure)
    , m_impl(impl)
{
}

JSWorker::~JSWorker()
{
    forgetDOMObject(*Heap::heap(this)->globalData(), m_impl.get());
}

JSObject* JSWorker::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSWorkerPrototype(JSWorkerPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSWorker::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSWorker, Base>(exec, &JSWorkerTable, this, propertyName, slot);
}

JSValue jsWorkerOnerror(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    Worker* imp = static_cast<Worker*>(static_cast<JSWorker*>(asObject(slot.slotBase()))->impl());
    if (EventListener* listener = imp->onerror()) {
        if (JSObject* jsFunction = listener->jsFunction())
            return jsFunction;
    }
    return jsNull();
}

JSValue jsWorkerOnmessage(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    Worker* imp = static_cast<Worker*>(static_cast<JSWorker*>(asObject(slot.slotBase()))->impl());
    if (EventListener* listener = imp->onmessage()) {
        if (JSObject* jsFunction = listener->jsFunction())
            return jsFunction;
    }
    return jsNull();
}

void JSWorker::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSWorker, Base>(exec, propertyName, value, &JSWorkerTable, this, slot);
}

void setJSWorkerOnerror(ExecState* exec, JSObject* thisObject, JSValue value)
{
    UNUSED_PARAM(exec);
    Worker* imp = static_cast<Worker*>(static_cast<JSWorker*>(thisObject)->impl());
    JSDOMGlobalObject* globalObject = toJSDOMGlobalObject(imp->scriptExecutionContext());
    if (!globalObject)
        return;
    imp->setOnerror(globalObject->createJSAttributeEventListener(value));
}

void setJSWorkerOnmessage(ExecState* exec, JSObject* thisObject, JSValue value)
{
    UNUSED_PARAM(exec);
    Worker* imp = static_cast<Worker*>(static_cast<JSWorker*>(thisObject)->impl());
    JSDOMGlobalObject* globalObject = toJSDOMGlobalObject(imp->scriptExecutionContext());
    if (!globalObject)
        return;
    imp->setOnmessage(globalObject->createJSAttributeEventListener(value));
}

JSValue JSC_HOST_CALL jsWorkerPrototypeFunctionPostMessage(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSWorker::s_info))
        return throwError(exec, TypeError);
    JSWorker* castedThisObj = static_cast<JSWorker*>(asObject(thisValue));
    Worker* imp = static_cast<Worker*>(castedThisObj->impl());
    const UString& message = args.at(0).toString(exec);

    imp->postMessage(message);
    return jsUndefined();
}

JSValue JSC_HOST_CALL jsWorkerPrototypeFunctionTerminate(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSWorker::s_info))
        return throwError(exec, TypeError);
    JSWorker* castedThisObj = static_cast<JSWorker*>(asObject(thisValue));
    Worker* imp = static_cast<Worker*>(castedThisObj->impl());

    imp->terminate();
    return jsUndefined();
}

JSValue JSC_HOST_CALL jsWorkerPrototypeFunctionAddEventListener(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSWorker::s_info))
        return throwError(exec, TypeError);
    JSWorker* castedThisObj = static_cast<JSWorker*>(asObject(thisValue));
    return castedThisObj->addEventListener(exec, args);
}

JSValue JSC_HOST_CALL jsWorkerPrototypeFunctionRemoveEventListener(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSWorker::s_info))
        return throwError(exec, TypeError);
    JSWorker* castedThisObj = static_cast<JSWorker*>(asObject(thisValue));
    return castedThisObj->removeEventListener(exec, args);
}

JSValue JSC_HOST_CALL jsWorkerPrototypeFunctionDispatchEvent(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSWorker::s_info))
        return throwError(exec, TypeError);
    JSWorker* castedThisObj = static_cast<JSWorker*>(asObject(thisValue));
    Worker* imp = static_cast<Worker*>(castedThisObj->impl());
    ExceptionCode ec = 0;
    Event* evt = toEvent(args.at(0));


    JSC::JSValue result = jsBoolean(imp->dispatchEvent(evt, ec));
    setDOMException(exec, ec);
    return result;
}

JSC::JSValue toJS(JSC::ExecState* exec, Worker* object)
{
    return getDOMObjectWrapper<JSWorker>(exec, object);
}
Worker* toWorker(JSC::JSValue value)
{
    return value.isObject(&JSWorker::s_info) ? static_cast<JSWorker*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(WORKERS)
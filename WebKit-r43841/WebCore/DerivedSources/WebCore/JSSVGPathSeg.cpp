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
#include "JSSVGPathSeg.h"

#include <wtf/GetPtr.h>

#include "KURL.h"
#include "SVGPathSeg.h"

#include <runtime/JSNumberCell.h>
#include <runtime/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGPathSeg);

/* Hash table */

static const HashTableValue JSSVGPathSegTableValues[4] =
{
    { "pathSegType", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPathSegType, (intptr_t)0 },
    { "pathSegTypeAsLetter", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPathSegTypeAsLetter, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsSVGPathSegConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGPathSegTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 7, JSSVGPathSegTableValues, 0 };
#else
    { 8, 7, JSSVGPathSegTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSSVGPathSegConstructorTableValues[21] =
{
    { "PATHSEG_UNKNOWN", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_UNKNOWN, (intptr_t)0 },
    { "PATHSEG_CLOSEPATH", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CLOSEPATH, (intptr_t)0 },
    { "PATHSEG_MOVETO_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_MOVETO_ABS, (intptr_t)0 },
    { "PATHSEG_MOVETO_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_MOVETO_REL, (intptr_t)0 },
    { "PATHSEG_LINETO_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_LINETO_ABS, (intptr_t)0 },
    { "PATHSEG_LINETO_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_LINETO_REL, (intptr_t)0 },
    { "PATHSEG_CURVETO_CUBIC_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CURVETO_CUBIC_ABS, (intptr_t)0 },
    { "PATHSEG_CURVETO_CUBIC_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CURVETO_CUBIC_REL, (intptr_t)0 },
    { "PATHSEG_CURVETO_QUADRATIC_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CURVETO_QUADRATIC_ABS, (intptr_t)0 },
    { "PATHSEG_CURVETO_QUADRATIC_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CURVETO_QUADRATIC_REL, (intptr_t)0 },
    { "PATHSEG_ARC_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_ARC_ABS, (intptr_t)0 },
    { "PATHSEG_ARC_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_ARC_REL, (intptr_t)0 },
    { "PATHSEG_LINETO_HORIZONTAL_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_LINETO_HORIZONTAL_ABS, (intptr_t)0 },
    { "PATHSEG_LINETO_HORIZONTAL_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_LINETO_HORIZONTAL_REL, (intptr_t)0 },
    { "PATHSEG_LINETO_VERTICAL_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_LINETO_VERTICAL_ABS, (intptr_t)0 },
    { "PATHSEG_LINETO_VERTICAL_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_LINETO_VERTICAL_REL, (intptr_t)0 },
    { "PATHSEG_CURVETO_CUBIC_SMOOTH_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CURVETO_CUBIC_SMOOTH_ABS, (intptr_t)0 },
    { "PATHSEG_CURVETO_CUBIC_SMOOTH_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CURVETO_CUBIC_SMOOTH_REL, (intptr_t)0 },
    { "PATHSEG_CURVETO_QUADRATIC_SMOOTH_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CURVETO_QUADRATIC_SMOOTH_ABS, (intptr_t)0 },
    { "PATHSEG_CURVETO_QUADRATIC_SMOOTH_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CURVETO_QUADRATIC_SMOOTH_REL, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGPathSegConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 2047, JSSVGPathSegConstructorTableValues, 0 };
#else
    { 70, 63, JSSVGPathSegConstructorTableValues, 0 };
#endif

class JSSVGPathSegConstructor : public DOMObject {
public:
    JSSVGPathSegConstructor(ExecState* exec)
        : DOMObject(JSSVGPathSegConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSSVGPathSegPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSSVGPathSegConstructor::s_info = { "SVGPathSegConstructor", 0, &JSSVGPathSegConstructorTable, 0 };

bool JSSVGPathSegConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGPathSegConstructor, DOMObject>(exec, &JSSVGPathSegConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSSVGPathSegPrototypeTableValues[21] =
{
    { "PATHSEG_UNKNOWN", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_UNKNOWN, (intptr_t)0 },
    { "PATHSEG_CLOSEPATH", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CLOSEPATH, (intptr_t)0 },
    { "PATHSEG_MOVETO_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_MOVETO_ABS, (intptr_t)0 },
    { "PATHSEG_MOVETO_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_MOVETO_REL, (intptr_t)0 },
    { "PATHSEG_LINETO_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_LINETO_ABS, (intptr_t)0 },
    { "PATHSEG_LINETO_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_LINETO_REL, (intptr_t)0 },
    { "PATHSEG_CURVETO_CUBIC_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CURVETO_CUBIC_ABS, (intptr_t)0 },
    { "PATHSEG_CURVETO_CUBIC_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CURVETO_CUBIC_REL, (intptr_t)0 },
    { "PATHSEG_CURVETO_QUADRATIC_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CURVETO_QUADRATIC_ABS, (intptr_t)0 },
    { "PATHSEG_CURVETO_QUADRATIC_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CURVETO_QUADRATIC_REL, (intptr_t)0 },
    { "PATHSEG_ARC_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_ARC_ABS, (intptr_t)0 },
    { "PATHSEG_ARC_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_ARC_REL, (intptr_t)0 },
    { "PATHSEG_LINETO_HORIZONTAL_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_LINETO_HORIZONTAL_ABS, (intptr_t)0 },
    { "PATHSEG_LINETO_HORIZONTAL_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_LINETO_HORIZONTAL_REL, (intptr_t)0 },
    { "PATHSEG_LINETO_VERTICAL_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_LINETO_VERTICAL_ABS, (intptr_t)0 },
    { "PATHSEG_LINETO_VERTICAL_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_LINETO_VERTICAL_REL, (intptr_t)0 },
    { "PATHSEG_CURVETO_CUBIC_SMOOTH_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CURVETO_CUBIC_SMOOTH_ABS, (intptr_t)0 },
    { "PATHSEG_CURVETO_CUBIC_SMOOTH_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CURVETO_CUBIC_SMOOTH_REL, (intptr_t)0 },
    { "PATHSEG_CURVETO_QUADRATIC_SMOOTH_ABS", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CURVETO_QUADRATIC_SMOOTH_ABS, (intptr_t)0 },
    { "PATHSEG_CURVETO_QUADRATIC_SMOOTH_REL", DontDelete|ReadOnly, (intptr_t)jsSVGPathSegPATHSEG_CURVETO_QUADRATIC_SMOOTH_REL, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGPathSegPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 2047, JSSVGPathSegPrototypeTableValues, 0 };
#else
    { 70, 63, JSSVGPathSegPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGPathSegPrototype::s_info = { "SVGPathSegPrototype", 0, &JSSVGPathSegPrototypeTable, 0 };

JSObject* JSSVGPathSegPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGPathSeg>(exec, globalObject);
}

bool JSSVGPathSegPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGPathSegPrototype, JSObject>(exec, &JSSVGPathSegPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSSVGPathSeg::s_info = { "SVGPathSeg", 0, &JSSVGPathSegTable, 0 };

JSSVGPathSeg::JSSVGPathSeg(PassRefPtr<Structure> structure, PassRefPtr<SVGPathSeg> impl, SVGElement* context)
    : DOMObject(structure)
    , m_context(context)
    , m_impl(impl)
{
}

JSSVGPathSeg::~JSSVGPathSeg()
{
    forgetDOMObject(*Heap::heap(this)->globalData(), m_impl.get());
}

JSObject* JSSVGPathSeg::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGPathSegPrototype(JSSVGPathSegPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSSVGPathSeg::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGPathSeg, Base>(exec, &JSSVGPathSegTable, this, propertyName, slot);
}

JSValue jsSVGPathSegPathSegType(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGPathSeg* imp = static_cast<SVGPathSeg*>(static_cast<JSSVGPathSeg*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->pathSegType());
}

JSValue jsSVGPathSegPathSegTypeAsLetter(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGPathSeg* imp = static_cast<SVGPathSeg*>(static_cast<JSSVGPathSeg*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->pathSegTypeAsLetter());
}

JSValue jsSVGPathSegConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSSVGPathSeg*>(asObject(slot.slotBase()))->getConstructor(exec);
}
JSValue JSSVGPathSeg::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSSVGPathSegConstructor>(exec);
}

// Constant getters

JSValue jsSVGPathSegPATHSEG_UNKNOWN(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(0));
}

JSValue jsSVGPathSegPATHSEG_CLOSEPATH(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(1));
}

JSValue jsSVGPathSegPATHSEG_MOVETO_ABS(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(2));
}

JSValue jsSVGPathSegPATHSEG_MOVETO_REL(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(3));
}

JSValue jsSVGPathSegPATHSEG_LINETO_ABS(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(4));
}

JSValue jsSVGPathSegPATHSEG_LINETO_REL(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(5));
}

JSValue jsSVGPathSegPATHSEG_CURVETO_CUBIC_ABS(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(6));
}

JSValue jsSVGPathSegPATHSEG_CURVETO_CUBIC_REL(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(7));
}

JSValue jsSVGPathSegPATHSEG_CURVETO_QUADRATIC_ABS(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(8));
}

JSValue jsSVGPathSegPATHSEG_CURVETO_QUADRATIC_REL(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(9));
}

JSValue jsSVGPathSegPATHSEG_ARC_ABS(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(10));
}

JSValue jsSVGPathSegPATHSEG_ARC_REL(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(11));
}

JSValue jsSVGPathSegPATHSEG_LINETO_HORIZONTAL_ABS(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(12));
}

JSValue jsSVGPathSegPATHSEG_LINETO_HORIZONTAL_REL(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(13));
}

JSValue jsSVGPathSegPATHSEG_LINETO_VERTICAL_ABS(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(14));
}

JSValue jsSVGPathSegPATHSEG_LINETO_VERTICAL_REL(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(15));
}

JSValue jsSVGPathSegPATHSEG_CURVETO_CUBIC_SMOOTH_ABS(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(16));
}

JSValue jsSVGPathSegPATHSEG_CURVETO_CUBIC_SMOOTH_REL(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(17));
}

JSValue jsSVGPathSegPATHSEG_CURVETO_QUADRATIC_SMOOTH_ABS(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(18));
}

JSValue jsSVGPathSegPATHSEG_CURVETO_QUADRATIC_SMOOTH_REL(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(19));
}

SVGPathSeg* toSVGPathSeg(JSC::JSValue value)
{
    return value.isObject(&JSSVGPathSeg::s_info) ? static_cast<JSSVGPathSeg*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(SVG)

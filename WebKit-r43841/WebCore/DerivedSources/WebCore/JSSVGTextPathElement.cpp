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
#include "JSSVGTextPathElement.h"

#include <wtf/GetPtr.h>

#include "JSSVGAnimatedEnumeration.h"
#include "JSSVGAnimatedLength.h"
#include "JSSVGAnimatedString.h"
#include "SVGTextPathElement.h"

#include <runtime/JSNumberCell.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGTextPathElement);

/* Hash table */

static const HashTableValue JSSVGTextPathElementTableValues[6] =
{
    { "startOffset", DontDelete|ReadOnly, (intptr_t)jsSVGTextPathElementStartOffset, (intptr_t)0 },
    { "method", DontDelete|ReadOnly, (intptr_t)jsSVGTextPathElementMethod, (intptr_t)0 },
    { "spacing", DontDelete|ReadOnly, (intptr_t)jsSVGTextPathElementSpacing, (intptr_t)0 },
    { "href", DontDelete|ReadOnly, (intptr_t)jsSVGTextPathElementHref, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsSVGTextPathElementConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGTextPathElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSSVGTextPathElementTableValues, 0 };
#else
    { 16, 15, JSSVGTextPathElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSSVGTextPathElementConstructorTableValues[7] =
{
    { "TEXTPATH_METHODTYPE_UNKNOWN", DontDelete|ReadOnly, (intptr_t)jsSVGTextPathElementTEXTPATH_METHODTYPE_UNKNOWN, (intptr_t)0 },
    { "TEXTPATH_METHODTYPE_ALIGN", DontDelete|ReadOnly, (intptr_t)jsSVGTextPathElementTEXTPATH_METHODTYPE_ALIGN, (intptr_t)0 },
    { "TEXTPATH_METHODTYPE_STRETCH", DontDelete|ReadOnly, (intptr_t)jsSVGTextPathElementTEXTPATH_METHODTYPE_STRETCH, (intptr_t)0 },
    { "TEXTPATH_SPACINGTYPE_UNKNOWN", DontDelete|ReadOnly, (intptr_t)jsSVGTextPathElementTEXTPATH_SPACINGTYPE_UNKNOWN, (intptr_t)0 },
    { "TEXTPATH_SPACINGTYPE_AUTO", DontDelete|ReadOnly, (intptr_t)jsSVGTextPathElementTEXTPATH_SPACINGTYPE_AUTO, (intptr_t)0 },
    { "TEXTPATH_SPACINGTYPE_EXACT", DontDelete|ReadOnly, (intptr_t)jsSVGTextPathElementTEXTPATH_SPACINGTYPE_EXACT, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGTextPathElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 31, JSSVGTextPathElementConstructorTableValues, 0 };
#else
    { 18, 15, JSSVGTextPathElementConstructorTableValues, 0 };
#endif

class JSSVGTextPathElementConstructor : public DOMObject {
public:
    JSSVGTextPathElementConstructor(ExecState* exec)
        : DOMObject(JSSVGTextPathElementConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSSVGTextPathElementPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSSVGTextPathElementConstructor::s_info = { "SVGTextPathElementConstructor", 0, &JSSVGTextPathElementConstructorTable, 0 };

bool JSSVGTextPathElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGTextPathElementConstructor, DOMObject>(exec, &JSSVGTextPathElementConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSSVGTextPathElementPrototypeTableValues[7] =
{
    { "TEXTPATH_METHODTYPE_UNKNOWN", DontDelete|ReadOnly, (intptr_t)jsSVGTextPathElementTEXTPATH_METHODTYPE_UNKNOWN, (intptr_t)0 },
    { "TEXTPATH_METHODTYPE_ALIGN", DontDelete|ReadOnly, (intptr_t)jsSVGTextPathElementTEXTPATH_METHODTYPE_ALIGN, (intptr_t)0 },
    { "TEXTPATH_METHODTYPE_STRETCH", DontDelete|ReadOnly, (intptr_t)jsSVGTextPathElementTEXTPATH_METHODTYPE_STRETCH, (intptr_t)0 },
    { "TEXTPATH_SPACINGTYPE_UNKNOWN", DontDelete|ReadOnly, (intptr_t)jsSVGTextPathElementTEXTPATH_SPACINGTYPE_UNKNOWN, (intptr_t)0 },
    { "TEXTPATH_SPACINGTYPE_AUTO", DontDelete|ReadOnly, (intptr_t)jsSVGTextPathElementTEXTPATH_SPACINGTYPE_AUTO, (intptr_t)0 },
    { "TEXTPATH_SPACINGTYPE_EXACT", DontDelete|ReadOnly, (intptr_t)jsSVGTextPathElementTEXTPATH_SPACINGTYPE_EXACT, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGTextPathElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 31, JSSVGTextPathElementPrototypeTableValues, 0 };
#else
    { 18, 15, JSSVGTextPathElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGTextPathElementPrototype::s_info = { "SVGTextPathElementPrototype", 0, &JSSVGTextPathElementPrototypeTable, 0 };

JSObject* JSSVGTextPathElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGTextPathElement>(exec, globalObject);
}

bool JSSVGTextPathElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGTextPathElementPrototype, JSObject>(exec, &JSSVGTextPathElementPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSSVGTextPathElement::s_info = { "SVGTextPathElement", &JSSVGTextContentElement::s_info, &JSSVGTextPathElementTable, 0 };

JSSVGTextPathElement::JSSVGTextPathElement(PassRefPtr<Structure> structure, PassRefPtr<SVGTextPathElement> impl)
    : JSSVGTextContentElement(structure, impl)
{
}

JSObject* JSSVGTextPathElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGTextPathElementPrototype(JSSVGTextPathElementPrototype::createStructure(JSSVGTextContentElementPrototype::self(exec, globalObject)));
}

bool JSSVGTextPathElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGTextPathElement, Base>(exec, &JSSVGTextPathElementTable, this, propertyName, slot);
}

JSValue jsSVGTextPathElementStartOffset(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGTextPathElement* imp = static_cast<SVGTextPathElement*>(static_cast<JSSVGTextPathElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedLength> obj = imp->startOffsetAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGTextPathElementMethod(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGTextPathElement* imp = static_cast<SVGTextPathElement*>(static_cast<JSSVGTextPathElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedEnumeration> obj = imp->methodAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGTextPathElementSpacing(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGTextPathElement* imp = static_cast<SVGTextPathElement*>(static_cast<JSSVGTextPathElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedEnumeration> obj = imp->spacingAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGTextPathElementHref(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    SVGTextPathElement* imp = static_cast<SVGTextPathElement*>(static_cast<JSSVGTextPathElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedString> obj = imp->hrefAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValue jsSVGTextPathElementConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSSVGTextPathElement*>(asObject(slot.slotBase()))->getConstructor(exec);
}
JSValue JSSVGTextPathElement::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSSVGTextPathElementConstructor>(exec);
}

// Constant getters

JSValue jsSVGTextPathElementTEXTPATH_METHODTYPE_UNKNOWN(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(0));
}

JSValue jsSVGTextPathElementTEXTPATH_METHODTYPE_ALIGN(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(1));
}

JSValue jsSVGTextPathElementTEXTPATH_METHODTYPE_STRETCH(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(2));
}

JSValue jsSVGTextPathElementTEXTPATH_SPACINGTYPE_UNKNOWN(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(0));
}

JSValue jsSVGTextPathElementTEXTPATH_SPACINGTYPE_AUTO(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(1));
}

JSValue jsSVGTextPathElementTEXTPATH_SPACINGTYPE_EXACT(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(2));
}


}

#endif // ENABLE(SVG)

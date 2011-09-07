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


#if ENABLE(SVG) && ENABLE(SVG_FONTS)

#include "SVGElement.h"
#include "JSSVGFontElement.h"

#include <wtf/GetPtr.h>

#include "SVGFontElement.h"


using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGFontElement);

/* Hash table for prototype */

static const HashTableValue JSSVGFontElementPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGFontElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGFontElementPrototypeTableValues, 0 };
#else
    { 1, 0, JSSVGFontElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGFontElementPrototype::s_info = { "SVGFontElementPrototype", 0, &JSSVGFontElementPrototypeTable, 0 };

JSObject* JSSVGFontElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGFontElement>(exec, globalObject);
}

const ClassInfo JSSVGFontElement::s_info = { "SVGFontElement", &JSSVGElement::s_info, 0, 0 };

JSSVGFontElement::JSSVGFontElement(PassRefPtr<Structure> structure, PassRefPtr<SVGFontElement> impl)
    : JSSVGElement(structure, impl)
{
}

JSObject* JSSVGFontElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGFontElementPrototype(JSSVGFontElementPrototype::createStructure(JSSVGElementPrototype::self(exec, globalObject)));
}


}

#endif // ENABLE(SVG) && ENABLE(SVG_FONTS)

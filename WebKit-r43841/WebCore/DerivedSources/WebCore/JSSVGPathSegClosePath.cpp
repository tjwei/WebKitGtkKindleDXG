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
#include "JSSVGPathSegClosePath.h"

#include <wtf/GetPtr.h>

#include "SVGPathSegClosePath.h"


using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGPathSegClosePath);

/* Hash table for prototype */

static const HashTableValue JSSVGPathSegClosePathPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGPathSegClosePathPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGPathSegClosePathPrototypeTableValues, 0 };
#else
    { 1, 0, JSSVGPathSegClosePathPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGPathSegClosePathPrototype::s_info = { "SVGPathSegClosePathPrototype", 0, &JSSVGPathSegClosePathPrototypeTable, 0 };

JSObject* JSSVGPathSegClosePathPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGPathSegClosePath>(exec, globalObject);
}

const ClassInfo JSSVGPathSegClosePath::s_info = { "SVGPathSegClosePath", &JSSVGPathSeg::s_info, 0, 0 };

JSSVGPathSegClosePath::JSSVGPathSegClosePath(PassRefPtr<Structure> structure, PassRefPtr<SVGPathSegClosePath> impl, SVGElement* context)
    : JSSVGPathSeg(structure, impl, context)
{
}

JSObject* JSSVGPathSegClosePath::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGPathSegClosePathPrototype(JSSVGPathSegClosePathPrototype::createStructure(JSSVGPathSegPrototype::self(exec, globalObject)));
}


}

#endif // ENABLE(SVG)
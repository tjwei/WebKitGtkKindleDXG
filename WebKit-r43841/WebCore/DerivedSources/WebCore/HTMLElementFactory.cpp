/*
 * THIS FILE IS AUTOMATICALLY GENERATED, DO NOT EDIT.
 *
 *
 * Copyright (C) 2005 Apple Computer, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */


#include "config.h"
#include "HTMLElementFactory.h"

#include "HTMLNames.h"
#if ENABLE(DASHBOARD_SUPPORT)
#include "Document.h"
#include "Settings.h"
#endif

#include "HTMLFormElement.h"
#include "HTMLAnchorElement.h"
#include "HTMLElement.h"
#include "HTMLAppletElement.h"
#include "HTMLAreaElement.h"
#include "HTMLBaseElement.h"
#include "HTMLBaseFontElement.h"
#include "HTMLBlockquoteElement.h"
#include "HTMLBodyElement.h"
#include "HTMLBRElement.h"
#include "HTMLButtonElement.h"
#include "HTMLCanvasElement.h"
#include "HTMLTableCaptionElement.h"
#include "HTMLTableColElement.h"
#include "HTMLModElement.h"
#include "HTMLDirectoryElement.h"
#include "HTMLDivElement.h"
#include "HTMLDListElement.h"
#include "HTMLEmbedElement.h"
#include "HTMLFieldSetElement.h"
#include "HTMLFontElement.h"
#include "HTMLFormElement.h"
#include "HTMLFrameElement.h"
#include "HTMLFrameSetElement.h"
#include "HTMLHeadingElement.h"
#include "HTMLHeadElement.h"
#include "HTMLHRElement.h"
#include "HTMLHtmlElement.h"
#include "HTMLIFrameElement.h"
#include "HTMLImageElement.h"
#include "HTMLInputElement.h"
#include "HTMLIsIndexElement.h"
#include "HTMLKeygenElement.h"
#include "HTMLLabelElement.h"
#include "HTMLLegendElement.h"
#include "HTMLLIElement.h"
#include "HTMLLinkElement.h"
#include "HTMLPreElement.h"
#include "HTMLMapElement.h"
#include "HTMLMarqueeElement.h"
#include "HTMLMenuElement.h"
#include "HTMLMetaElement.h"
#include "HTMLObjectElement.h"
#include "HTMLOListElement.h"
#include "HTMLOptGroupElement.h"
#include "HTMLOptionElement.h"
#include "HTMLParagraphElement.h"
#include "HTMLParamElement.h"
#include "HTMLQuoteElement.h"
#include "HTMLScriptElement.h"
#include "HTMLSelectElement.h"
#include "HTMLStyleElement.h"
#include "HTMLTableElement.h"
#include "HTMLTableSectionElement.h"
#include "HTMLTableCellElement.h"
#include "HTMLTextAreaElement.h"
#include "HTMLTitleElement.h"
#include "HTMLTableRowElement.h"
#include "HTMLUListElement.h"
#include <wtf/HashMap.h>

namespace WebCore {

using namespace HTMLNames;

typedef PassRefPtr<HTMLElement> (*ConstructorFunction)(const QualifiedName&, Document*, HTMLFormElement*, bool createdByParser);
typedef HashMap<AtomicStringImpl*, ConstructorFunction> FunctionMap;

static FunctionMap* gFunctionMap = 0;

static PassRefPtr<HTMLElement> anchorConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLAnchorElement(tagName, doc);
}

static PassRefPtr<HTMLElement> appletConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLAppletElement(tagName, doc);
}

static PassRefPtr<HTMLElement> areaConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLAreaElement(tagName, doc);
}

static PassRefPtr<HTMLElement> baseConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLBaseElement(tagName, doc);
}

static PassRefPtr<HTMLElement> basefontConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLBaseFontElement(tagName, doc);
}

static PassRefPtr<HTMLElement> blockquoteConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLBlockquoteElement(tagName, doc);
}

static PassRefPtr<HTMLElement> bodyConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLBodyElement(tagName, doc);
}

static PassRefPtr<HTMLElement> brConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLBRElement(tagName, doc);
}

static PassRefPtr<HTMLElement> buttonConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement* formElement, bool)
{
    return new HTMLButtonElement(tagName, doc, formElement);
}

static PassRefPtr<HTMLElement> canvasConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLCanvasElement(tagName, doc);
}

static PassRefPtr<HTMLElement> tablecaptionConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLTableCaptionElement(tagName, doc);
}

static PassRefPtr<HTMLElement> tablecolConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLTableColElement(tagName, doc);
}

static PassRefPtr<HTMLElement> modConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLModElement(tagName, doc);
}

static PassRefPtr<HTMLElement> directoryConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLDirectoryElement(tagName, doc);
}

static PassRefPtr<HTMLElement> divConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLDivElement(tagName, doc);
}

static PassRefPtr<HTMLElement> dlistConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLDListElement(tagName, doc);
}

static PassRefPtr<HTMLElement> embedConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLEmbedElement(tagName, doc);
}

static PassRefPtr<HTMLElement> fieldsetConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement* formElement, bool)
{
    return new HTMLFieldSetElement(tagName, doc, formElement);
}

static PassRefPtr<HTMLElement> fontConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLFontElement(tagName, doc);
}

static PassRefPtr<HTMLElement> formConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLFormElement(tagName, doc);
}

static PassRefPtr<HTMLElement> frameConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLFrameElement(tagName, doc);
}

static PassRefPtr<HTMLElement> framesetConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLFrameSetElement(tagName, doc);
}

static PassRefPtr<HTMLElement> headingConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLHeadingElement(tagName, doc);
}

static PassRefPtr<HTMLElement> headConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLHeadElement(tagName, doc);
}

static PassRefPtr<HTMLElement> hrConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLHRElement(tagName, doc);
}

static PassRefPtr<HTMLElement> htmlConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLHtmlElement(tagName, doc);
}

static PassRefPtr<HTMLElement> iframeConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLIFrameElement(tagName, doc);
}

static PassRefPtr<HTMLElement> imageConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement* formElement, bool)
{
    return new HTMLImageElement(tagName, doc, formElement);
}

static PassRefPtr<HTMLElement> inputConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement* formElement, bool)
{
    return new HTMLInputElement(tagName, doc, formElement);
}

static PassRefPtr<HTMLElement> isindexConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement* formElement, bool)
{
    return new HTMLIsIndexElement(tagName, doc, formElement);
}

static PassRefPtr<HTMLElement> keygenConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement* formElement, bool)
{
    return new HTMLKeygenElement(tagName, doc, formElement);
}

static PassRefPtr<HTMLElement> labelConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLLabelElement(tagName, doc);
}

static PassRefPtr<HTMLElement> legendConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement* formElement, bool)
{
    return new HTMLLegendElement(tagName, doc, formElement);
}

static PassRefPtr<HTMLElement> liConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLLIElement(tagName, doc);
}

static PassRefPtr<HTMLElement> linkConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool createdByParser)
{
    return new HTMLLinkElement(tagName, doc, createdByParser);
}

static PassRefPtr<HTMLElement> preConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLPreElement(tagName, doc);
}

static PassRefPtr<HTMLElement> mapConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLMapElement(tagName, doc);
}

static PassRefPtr<HTMLElement> marqueeConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLMarqueeElement(tagName, doc);
}

static PassRefPtr<HTMLElement> menuConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLMenuElement(tagName, doc);
}

static PassRefPtr<HTMLElement> metaConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLMetaElement(tagName, doc);
}

static PassRefPtr<HTMLElement> objectConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool createdByParser)
{
    return new HTMLObjectElement(tagName, doc, createdByParser);
}

static PassRefPtr<HTMLElement> olistConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLOListElement(tagName, doc);
}

static PassRefPtr<HTMLElement> optgroupConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement* formElement, bool)
{
    return new HTMLOptGroupElement(tagName, doc, formElement);
}

static PassRefPtr<HTMLElement> optionConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement* formElement, bool)
{
    return new HTMLOptionElement(tagName, doc, formElement);
}

static PassRefPtr<HTMLElement> paragraphConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLParagraphElement(tagName, doc);
}

static PassRefPtr<HTMLElement> paramConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLParamElement(tagName, doc);
}

static PassRefPtr<HTMLElement> quoteConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLQuoteElement(tagName, doc);
}

static PassRefPtr<HTMLElement> scriptConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool createdByParser)
{
    return new HTMLScriptElement(tagName, doc, createdByParser);
}

static PassRefPtr<HTMLElement> selectConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement* formElement, bool)
{
    return new HTMLSelectElement(tagName, doc, formElement);
}

static PassRefPtr<HTMLElement> styleConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool createdByParser)
{
    return new HTMLStyleElement(tagName, doc, createdByParser);
}

static PassRefPtr<HTMLElement> tableConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLTableElement(tagName, doc);
}

static PassRefPtr<HTMLElement> tablesectionConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLTableSectionElement(tagName, doc);
}

static PassRefPtr<HTMLElement> tablecellConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLTableCellElement(tagName, doc);
}

static PassRefPtr<HTMLElement> textareaConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement* formElement, bool)
{
    return new HTMLTextAreaElement(tagName, doc, formElement);
}

static PassRefPtr<HTMLElement> titleConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLTitleElement(tagName, doc);
}

static PassRefPtr<HTMLElement> tablerowConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLTableRowElement(tagName, doc);
}

static PassRefPtr<HTMLElement> ulistConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement*, bool)
{
    return new HTMLUListElement(tagName, doc);
}

static PassRefPtr<HTMLElement> imgToimageConstructor(const QualifiedName& tagName, Document* doc, HTMLFormElement* formElement, bool)
{
    return new HTMLImageElement(QualifiedName(tagName.prefix(), imgTag.localName(), tagName.namespaceURI()), doc, formElement);
}

static void addTag(const QualifiedName& tag, ConstructorFunction func)
{
    gFunctionMap->set(tag.localName().impl(), func);
}

static inline void createFunctionMapIfNecessary()
{
    if (gFunctionMap)
        return;
    // Create the table.
    gFunctionMap = new FunctionMap;
    
    // Populate it with constructor functions.
    addTag(aTag, anchorConstructor);
    addTag(appletTag, appletConstructor);
    addTag(areaTag, areaConstructor);
    addTag(baseTag, baseConstructor);
    addTag(basefontTag, basefontConstructor);
    addTag(blockquoteTag, blockquoteConstructor);
    addTag(bodyTag, bodyConstructor);
    addTag(brTag, brConstructor);
    addTag(buttonTag, buttonConstructor);
    addTag(canvasTag, canvasConstructor);
    addTag(captionTag, tablecaptionConstructor);
    addTag(colTag, tablecolConstructor);
    addTag(colgroupTag, tablecolConstructor);
    addTag(delTag, modConstructor);
    addTag(dirTag, directoryConstructor);
    addTag(divTag, divConstructor);
    addTag(dlTag, dlistConstructor);
    addTag(embedTag, embedConstructor);
    addTag(fieldsetTag, fieldsetConstructor);
    addTag(fontTag, fontConstructor);
    addTag(formTag, formConstructor);
    addTag(frameTag, frameConstructor);
    addTag(framesetTag, framesetConstructor);
    addTag(h1Tag, headingConstructor);
    addTag(h2Tag, headingConstructor);
    addTag(h3Tag, headingConstructor);
    addTag(h4Tag, headingConstructor);
    addTag(h5Tag, headingConstructor);
    addTag(h6Tag, headingConstructor);
    addTag(headTag, headConstructor);
    addTag(hrTag, hrConstructor);
    addTag(htmlTag, htmlConstructor);
    addTag(iframeTag, iframeConstructor);
    addTag(imageTag, imgToimageConstructor);
    addTag(imgTag, imageConstructor);
    addTag(inputTag, inputConstructor);
    addTag(insTag, modConstructor);
    addTag(isindexTag, isindexConstructor);
    addTag(keygenTag, keygenConstructor);
    addTag(labelTag, labelConstructor);
    addTag(legendTag, legendConstructor);
    addTag(liTag, liConstructor);
    addTag(linkTag, linkConstructor);
    addTag(listingTag, preConstructor);
    addTag(mapTag, mapConstructor);
    addTag(marqueeTag, marqueeConstructor);
    addTag(menuTag, menuConstructor);
    addTag(metaTag, metaConstructor);
    addTag(objectTag, objectConstructor);
    addTag(olTag, olistConstructor);
    addTag(optgroupTag, optgroupConstructor);
    addTag(optionTag, optionConstructor);
    addTag(pTag, paragraphConstructor);
    addTag(paramTag, paramConstructor);
    addTag(preTag, preConstructor);
    addTag(qTag, quoteConstructor);
    addTag(scriptTag, scriptConstructor);
    addTag(selectTag, selectConstructor);
    addTag(styleTag, styleConstructor);
    addTag(tableTag, tableConstructor);
    addTag(tbodyTag, tablesectionConstructor);
    addTag(tdTag, tablecellConstructor);
    addTag(textareaTag, textareaConstructor);
    addTag(tfootTag, tablesectionConstructor);
    addTag(thTag, tablecellConstructor);
    addTag(theadTag, tablesectionConstructor);
    addTag(titleTag, titleConstructor);
    addTag(trTag, tablerowConstructor);
    addTag(ulTag, ulistConstructor);
    addTag(xmpTag, preConstructor);
}

PassRefPtr<HTMLElement> HTMLElementFactory::createHTMLElement(const QualifiedName& qName, Document* doc, HTMLFormElement* formElement, bool createdByParser)
{
    // Don't make elements without a document
    if (!doc)
        return 0;

    createFunctionMapIfNecessary();
    ConstructorFunction func = gFunctionMap->get(qName.localName().impl());
    if (func)
        return func(qName, doc, formElement, createdByParser);
    return new HTMLElement(qName, doc);
}

} // namespace WebCore


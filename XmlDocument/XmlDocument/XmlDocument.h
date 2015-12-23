#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H
///////////////////////////////////////////////////////////////////
// XmlDocument.h - a container of XmlElement nodes               //
// Ver 1.2                                                       //
// Application: Help for CSE687 Pr#2, Spring 2015                //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013   //
// Author:      Sridhar Ganapthy, CST 4-187, 443-3948            //
//             SUID: 266711369, Email_id: sganapat@syr.edu       //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
This package is meant for searching the xml components with the help of the xml element.
The package helps to meet out all the requirements required to build the application
*
* Required Files:
* ---------------
*   - XmlDocument.h, XmlDocument.cpp, 
*     XmlElement.h, XmlElement.cpp
*	  XmlParser.h, XmlParser.cpp
* Build Process:
* --------------
*   cl /EHa /DTEST_DOCUMENT XmlDocument.cpp
*
* Maintenance History:
* --------------------
ver 1.2 : 28 Mar 15 - final version 
ver 1.1 : 21 Mar 15 - made minor changes with the methods present
* Ver 1.0 : 11 Feb 15
* - first release
*/

#include <memory>
#include <string>
#include "../XmlElement/XmlElement.h"
#include"../../../XmlParser/XmlParser.h"

namespace XmlProcessing
{
  class XmlDocument
  {
  public:
    using sPtr = std::shared_ptr < AbstractXmlElement > ;

    enum sourceType { string, filename };
/*
    XmlDocument(const std::string& src, sourceType srcType=string);*/
	XmlDocument(){}
    // queries return XmlDocument references so they can be chained, e.g., doc.element("foobar").descendents();

    XmlDocument& element(const std::string& tag);           // found_[0] contains first element (DFS order) with tag
    XmlDocument& elements(const std::string& tag);          // found_ contains all elements with tag
    XmlDocument& children(const std::string& tag = "");     // found_ contains sPtrs to children of prior found_[0] 
    XmlDocument& descendents(const std::string& tag = "");  // found_ contains sPtrs to descendents of prior found_[0]
    std::vector<sPtr>& select();                            // return reference to found_.  Use std::move(found_) to clear found_
	std::shared_ptr < AbstractXmlElement > GenerateTree(std::string InputString);
	std::shared_ptr < AbstractXmlElement > DFSSearchTree_forAttribute(std::shared_ptr < AbstractXmlElement > tempElem, std::string Attribute);
	bool DFSSearchTree_toaddchild(std::shared_ptr < AbstractXmlElement > tempElem, std::string tagforchild, std::string tag, std::string attribute, std::string value, std::string text);
	void XmlDisplay(std::shared_ptr < AbstractXmlElement > tempElem);
	bool DFSSearchTree_toremovechild(std::shared_ptr < AbstractXmlElement > tempElem, std::string parent, std::string removechild);
	void DFSSearchTree_toremoveAttribute(std::shared_ptr < AbstractXmlElement > tempElem, std::string Attribute);
	void DFSSearchTree_vectoroftag(std::shared_ptr < AbstractXmlElement > tempElem, std::string parent, std::string removechild);
	std::vector<std::shared_ptr<AbstractXmlElement>> DFSSearchTree_vectoroftag(std::shared_ptr < AbstractXmlElement > tempElem, std::string parent);
	bool DFSSearchTree_addchildbyattribute(std::shared_ptr < AbstractXmlElement > tempElem, std::string ParentAttribute, std::string childtag, std::string childattribute, std::string childvalue, std::string childtext);
	bool DFSSearchTree_removechildbyattribute(std::shared_ptr < AbstractXmlElement > tempElem, std::string ParentAttribute, std::string childtag);
	std::vector<std::pair<std::string, std::string>> DFSSearchTree_getvectorofattributes(std::shared_ptr < AbstractXmlElement > tempElem);
	std::vector<std::shared_ptr<AbstractXmlElement>> DFSSearchTree_getvectorofchildren(std::shared_ptr < AbstractXmlElement > tempElem);
	std::shared_ptr < AbstractXmlElement > DFSSearchTree_forAttribute(std::shared_ptr < AbstractXmlElement > tempElem, std::string parent, std::string attributenaem, std::string attributevalue);
	bool DFSSearchTree_addAttribute(std::shared_ptr < AbstractXmlElement > tempElem, std::string parent, std::string attributename, std::string attributevalue);
	bool DFSSearchTree_toremoveAttribute(std::shared_ptr < AbstractXmlElement > tempElem, std::string parent, std::string attributename);
	TaggedElement moveTaggedElements_requirement();

  private:
    sPtr pDocElement_;         // AST that holds procInstr, comments, XML root, and more comments
    std::vector<sPtr> found_;  // query results
  };
}
#endif

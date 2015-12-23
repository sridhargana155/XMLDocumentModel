/////////////////////////////////////////////////////////////////////////////
// DisplayPackage.cpp - Searches for the needed xml compnenets             //
//                                         through xml element             //
//		       				                                               //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// copyright ©   Sridhar Ganapathy                                         //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++ version 11, Visual Studio 2013                  //
// Platform:    Lenovo Z510, Core i7, Windows 8.1                          //
//									                                       //
// Author: Sridhar Ganapathy,CST,  Syracuse University                     //
//				SUID: 266711369, Email_id: sganapat@syr.edu                //
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include<stack>
#include "XmlDocument.h"
using namespace XmlProcessing;

//----------------Generates tree from the Xml Parser-------------------------------------------------------
std::shared_ptr < AbstractXmlElement > XmlDocument::GenerateTree(std::string InputString)
{
	XmlParser XmlPrs;
	pDocElement_ = XmlPrs.XmlConstructtree(InputString);
	return pDocElement_;
}

//--------------------Display to test this package locally-------------------------------------------
void XmlDocument::XmlDisplay(std::shared_ptr < AbstractXmlElement > tempElem) 
{
	std::cout << " " << tempElem->toString();
}


//-----------------------------------------------REQUIREMENT 4------------------------------------------------------------------------------//
//---------------------- Move Construction and Move Assignment-------------------------------------------------------------------
TaggedElement XmlDocument::moveTaggedElements_requirement()
{
	TaggedElement newtag("Student");
	std::vector<std::string>newElementAttributes = { "Name", "Sridhar", "School", "Syracuse University" };
	for (size_t i = 0; i < newElementAttributes.size(); i += 2)
		newtag.addAttrib(newElementAttributes[i], newElementAttributes[i + 1]);
	/*std::cout << std::endl << "newly created tagged element inside a function :\n" << newtag.toString() << std::endl;*/
	std::cout << std::endl << "A new tag element :\n" << newtag.toString() << std::endl;
	return newtag;
}

//-----------------------------------------------REQUIREMENT 5------------------------------------------------------------------------------//

std::shared_ptr < AbstractXmlElement > XmlDocument::DFSSearchTree_forAttribute(std::shared_ptr < AbstractXmlElement > tempElem, std::string Attribute)
{
	
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	std::stack<sPtr> nodeStack;
	nodeStack.push(tempElem);
	sPtr pCurrentNode = NULL;
	while (nodeStack.size() > 0)
	{
		pCurrentNode = nodeStack.top();// declared outside while loop
		nodeStack.pop();
		for (auto tmp: pCurrentNode->Attribute())
		{
			if (tmp.first.c_str() == Attribute)
			{
				return pCurrentNode;
				break;
			}
		}

		size_t numChildren = pCurrentNode->Children().size();
		for (size_t i = 0; i < numChildren; ++i)
			nodeStack.push(pCurrentNode->Children()[numChildren - i - 1]);
		pCurrentNode = NULL;
	}

}

//------------------------------------------------------<REQUIREMENT 7>----------------------------------------------------------------------------------------------------
//------------------------------------------------ADD CHILD BY TAG NAME-----------------------------------------------------------------------------------------
bool XmlDocument::DFSSearchTree_toaddchild(std::shared_ptr < AbstractXmlElement > tempElem,std::string tagforchild, std::string tag, std::string attribute, std::string value,std::string text)
{
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	std::stack<sPtr> nodeStack;
	nodeStack.push(tempElem);
	sPtr pCurrentNode = NULL;
	while (nodeStack.size() > 0)
	{
		pCurrentNode = nodeStack.top();// declared outside while loop
		nodeStack.pop();
		if (pCurrentNode->value() == tagforchild)
		{
			std::string content = pCurrentNode->toString(); size_t contentsize = content.size();
			if (content[contentsize - 2] == '/' || content[contentsize - 2] == '!' || content[contentsize - 2] == '?')
			{
				return false;
				break;
			}	
			else
			{
				//add all child and other things
				sPtr child = makeTaggedElement(tag);
				child->addAttrib(attribute, value);
				child->addChild(makeTextElement(text));
				pCurrentNode->addChild(child);
				return true;
				break;
			}

	}
		size_t numChildren = pCurrentNode->Children().size();
		for (size_t i = 0; i < numChildren; ++i)
			nodeStack.push(pCurrentNode->Children()[numChildren - i - 1]);
		pCurrentNode = NULL;
	}
	std::cout << "There is no tag found by this name\n";
	return false;
}

//-------------------------------------------------------------REQUIREMENT 7-------------------------------------------------------------------------
//------------------------------------------------REMOVE CHILD BY TAG NAME-----------------------------------------------------------------------------------------
bool XmlDocument::DFSSearchTree_toremovechild(std::shared_ptr < AbstractXmlElement > tempElem, std::string parent, std::string removechild)
{
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	std::stack<sPtr> nodeStack;
	nodeStack.push(tempElem);
	sPtr pCurrentNode = NULL;
	while (nodeStack.size() > 0)
	{
		pCurrentNode = nodeStack.top();// declared outside while loop
		nodeStack.pop();
		if (pCurrentNode->value() == parent)
		{			//add all child and other things

			std::string content = pCurrentNode->toString(); size_t contentsize = content.size();
			if (content[contentsize - 2] == '/' || content[contentsize - 2] == '!' || content[contentsize - 2] == '?')
			{
				return false;
				break;
			}
			else
			{
			 for (auto tmp : pCurrentNode->Children())
				{
				  if (tmp->value() == removechild)
					{
					pCurrentNode->removeChild(tmp);
					return true;
					break;
					}

				}
		   }
		}
			size_t numChildren = pCurrentNode->Children().size();
			for (size_t i = 0; i < numChildren; ++i)
				nodeStack.push(pCurrentNode->Children()[numChildren - i - 1]);
			pCurrentNode = NULL;
	}
	std::cout << "There is no tag found by this name\n";
	return false;
}

//-----------------------------------------------REQUIREMENT 7------------------------------------------------------------------------------//
//----------------------------------------------------ADD CHILD BY ATTRIBUTE----------------------------------------------------------------//

bool XmlDocument::DFSSearchTree_addchildbyattribute(std::shared_ptr < AbstractXmlElement > tempElem, std::string ParentAttribute, std::string childtag, std::string childattribute, std::string childvalue, std::string childtext)
{
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	std::stack<sPtr> nodeStack;
	nodeStack.push(tempElem);
	sPtr pCurrentNode = NULL;
	while (nodeStack.size() > 0)
	{
		pCurrentNode = nodeStack.top();// declared outside while loop
		nodeStack.pop();
		for (auto tmp : pCurrentNode->Attribute())
		{
			if (tmp.first.c_str() == ParentAttribute)
			{
				std::string content = pCurrentNode->toString(); size_t contentsize = content.size();
				if (content[contentsize - 2] == '/' || content[contentsize - 2] == '!' || content[contentsize - 2] == '?')
				{
					return false;
					break;
				}
				else
				{
					//add all child and other things
					sPtr child = makeTaggedElement(childtag);
					child->addAttrib(childattribute, childvalue);
					child->addChild(makeTextElement(childtext));
					pCurrentNode->addChild(child);
					return true;
					break;
				}
			}
		}
		size_t numChildren = pCurrentNode->Children().size();
		for (size_t i = 0; i < numChildren; ++i)
			nodeStack.push(pCurrentNode->Children()[numChildren - i - 1]);
		pCurrentNode = NULL;
	}
	std::cout << "The attribute searched could not be found\n";
	return false;
}

//-----------------------------------------------REQUIREMENT 7------------------------------------------------------------------------------//
//----------------------------------------------------REMOVE CHILD BY ATTRIBUTE----------------------------------------------------------------//

bool XmlDocument::DFSSearchTree_removechildbyattribute(std::shared_ptr < AbstractXmlElement > tempElem, std::string ParentAttribute, std::string childtag)
{
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	std::stack<sPtr> nodeStack;
	nodeStack.push(tempElem);
	sPtr pCurrentNode = NULL;
	while (nodeStack.size() > 0)
	{
		pCurrentNode = nodeStack.top();// declared outside while loop
		nodeStack.pop();
		// searching done here - if found break=> pCurrentNode
		/*for (size_t i = 0; i<attribs.size(); ++i)
		std::cout << "\n  attributes: " << attribs[i].first.c_str() << ", " << attribs[i].second.c_str();*/
		for (auto tmp : pCurrentNode->Attribute())
		{
			if (tmp.first.c_str() == ParentAttribute)
			{
				std::string content = pCurrentNode->toString(); size_t contentsize = content.size();
				if (content[contentsize - 2] == '/' || content[contentsize - 2] == '!' || content[contentsize - 2] == '?')
				{
					return false;
					break;
				}
				else
				{
					for (auto tmp : pCurrentNode->Children())
					{
						if (tmp->value() == childtag)
						{
							pCurrentNode->removeChild(tmp);
							return true;
							break;
						}

					}
					
				}
		}
}
		size_t numChildren = pCurrentNode->Children().size();
		for (size_t i = 0; i < numChildren; ++i)
			nodeStack.push(pCurrentNode->Children()[numChildren - i - 1]);
		pCurrentNode = NULL;
}
	std::cout << "The attribute searched could not be found\n";
	return false;
}


//-----------------------------------------------REQUIREMENT 8------------------------------------------------------------------------------//
//------------------------------------Returning the vector of attributes for a given element pointer---------------------------------------------------------------------//

std::vector<std::pair<std::string, std::string>> XmlDocument::DFSSearchTree_getvectorofattributes(std::shared_ptr < AbstractXmlElement > tempElem)
{
	std::vector<std::pair<std::string, std::string>> Vectorofattributes;
	Vectorofattributes = tempElem->Attribute();
	return Vectorofattributes;
}


//-----------------------------------------------REQUIREMENT 8------------------------------------------------------------------------------//
//------------------------------------Returning the vector of children for a specified element---------------------------------------------------------------------//

std::vector<std::shared_ptr<AbstractXmlElement>> XmlDocument::DFSSearchTree_getvectorofchildren(std::shared_ptr < AbstractXmlElement > tempElem)
{
	std::vector<std::shared_ptr<AbstractXmlElement>> VectorofChildren;
	VectorofChildren = tempElem->Children();
	return VectorofChildren;
}


//-----------------------------------------------REQUIREMENT 9------------------------------------------------------------------------------//
//---------------------------------providing the ability to add an attribute name-value pair------------------------------------------------//
bool XmlDocument::DFSSearchTree_addAttribute(std::shared_ptr < AbstractXmlElement > tempElem, std::string parent,std::string attributename,std::string attributevalue)
{
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	std::stack<sPtr> nodeStack;
	nodeStack.push(tempElem);
	sPtr pCurrentNode = NULL;
	while (nodeStack.size() > 0)
	{
		pCurrentNode = nodeStack.top();// declared outside while loop
		nodeStack.pop();
		if (pCurrentNode->value() == parent)
		{			//add all child and other things

			std::string content = pCurrentNode->toString(); size_t contentsize = content.size();
			if (content[contentsize - 2] == '!')
			{
				return false;
				break;
			}
			else
			{
				pCurrentNode->addAttrib(attributename, attributevalue);
				return true;
				break;
			}
		}
		size_t numChildren = pCurrentNode->Children().size();
		for (size_t i = 0; i < numChildren; ++i)
			nodeStack.push(pCurrentNode->Children()[numChildren - i - 1]);
		pCurrentNode = NULL;
	}
	std::cout << "The tag searched for is not found\n";
	return false;
}
//-----------------------------------------------REQUIREMENT 9------------------------------------------------------------------------------//
//---------------------------------providing the ability to remove an attribute name-value pair------------------------------------------------//

bool XmlDocument::DFSSearchTree_toremoveAttribute(std::shared_ptr < AbstractXmlElement > tempElem, std::string parent, std::string attributename)
{
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	std::stack<sPtr> nodeStack;
	nodeStack.push(tempElem);
	sPtr pCurrentNode = NULL;
	while (nodeStack.size() > 0)
	{
		pCurrentNode = nodeStack.top();// declared outside while loop
		nodeStack.pop();
		if (pCurrentNode->value() == parent)
		{			//add all child and other things

			std::string content = pCurrentNode->toString(); size_t contentsize = content.size();
			if (content[contentsize - 2] == '!')
			{
				return false;
				break;
			}
			else
			{
				pCurrentNode->removeAttrib(attributename);
				return true;
				break;
			}
		}
		size_t numChildren = pCurrentNode->Children().size();
		for (size_t i = 0; i < numChildren; ++i)
			nodeStack.push(pCurrentNode->Children()[numChildren - i - 1]);
		pCurrentNode = NULL;
	}
	std::cout << "The tag searched for is not found\n";
	return false;
}


//-------------------------------------------------------------------<REQUIREMENET 6>----------------------------------------------------------------------------------
std::vector<std::shared_ptr<AbstractXmlElement>> XmlDocument::DFSSearchTree_vectoroftag(std::shared_ptr < AbstractXmlElement > tempElem, std::string parent)
{
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	std::vector<std::shared_ptr<AbstractXmlElement>> vecotoftagpointers;
	std::stack<sPtr> nodeStack;
	nodeStack.push(tempElem);
	sPtr pCurrentNode = NULL;
	while (nodeStack.size() > 0)
	{
		pCurrentNode = nodeStack.top();// declared outside while loop
		nodeStack.pop();
		if (pCurrentNode->value() == parent)
		{			//add all child and other things
			vecotoftagpointers.push_back(pCurrentNode);
		}
		size_t numChildren = pCurrentNode->Children().size();
		for (size_t i = 0; i < numChildren; ++i)
			nodeStack.push(pCurrentNode->Children()[numChildren - i - 1]);
		pCurrentNode = NULL;
	}
	return vecotoftagpointers;
}


// Test stub to test this package
#ifdef TEST_DOCUMENT

int main()
{
	using sPtr = std::shared_ptr < AbstractXmlElement >;
  XmlDocument Xmldoc1;
  sPtr checker;
  std::string testingString = "<parent att1='val1' att2='val2'>Parent Text Element<child1 /><child2 sri='dhar' sree='ram' jothi='mathi'>child2 body<child1 /></child2></parent>";
  checker = Xmldoc1.GenerateTree(testingString);
  Xmldoc1.XmlDisplay(checker);
  sPtr PointerforAttribute;
  PointerforAttribute = Xmldoc1.DFSSearchTree_forAttribute(checker, "sri");
  Xmldoc1.XmlDisplay(checker);
  if (Xmldoc1.DFSSearchTree_toaddchild(checker, "parent", "child2", "sri", "haran", "It is me") == true)
	  std::cout << "\nChild added successfully";
  if (Xmldoc1.DFSSearchTree_toremovechild(checker, "parent", "child2") == true)
	  std::cout << "\nChild removed successfully";
  if (Xmldoc1.DFSSearchTree_addchildbyattribute(checker, "att1", "child3", "att3", "val3", "I'm child3") == true)
	  std::cout << "\nChild added successfully";
  if (Xmldoc1.DFSSearchTree_removechildbyattribute(checker, "parent", "child3") == true)
	  std::cout << "\nChild removed successfully";
  std::vector<std::pair<std::string, std::string>> demo;
  std::vector<std::shared_ptr<AbstractXmlElement>>demo1, demo2;
  demo = Xmldoc1.DFSSearchTree_getvectorofattributes(PointerforAttribute);
  for (auto tmp : demo)
	  std::cout << tmp.first<<tmp.second;
  demo1 = Xmldoc1.DFSSearchTree_getvectorofchildren(PointerforAttribute);
  for (auto tmp : demo1)
	  std::cout << tmp->toString();
  std::cout << "\n\n";
  if (Xmldoc1.DFSSearchTree_addAttribute(checker, "parent", "newatt", "newval") == true)
	  std::cout << "\nAttribute added successfully";
  if (Xmldoc1.DFSSearchTree_toremoveAttribute(checker, "parent", "newatt") == true)
	  std::cout << "\nAttribute removed successfully";
  demo2 = Xmldoc1.DFSSearchTree_vectoroftag(checker, "parent");
  for (auto tmp : demo2)
	  std::cout << tmp->toString();
  return 0;
}

#endif 
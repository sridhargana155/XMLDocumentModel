/////////////////////////////////////////////////////////////////////////////
// Executive.cpp -   Controls the main flow execution for this application //
//				                                                           //
// ----------------------------------------------------------------------- //
// copyright ©  Sridhar Ganapathy                                          //
// All rights granted provided that this notice is retained                //
// ----------------------------------------------------------------------- //
// Language:    Visual C++ version 11, Visual Studio 2013                  //
// Platform:    Lenovo Z510, Core i7, Windows 8.1                          //
//									                                       //
// Author: Sridhar Ganapathy,CST,  Syracuse University		               //
//				SUID: 266711369, Email_id: sganapat@syr.edu                //
/////////////////////////////////////////////////////////////////////////////
#include"XmlDocument\XmlDocument\XmlDocument.h"
#include"../DisplayPackage/DisplayPackage.h"
#include <iostream>
#include<vector>
#include<string>
#include <fstream>
using namespace std;

//----------------------------The main flow of execution begins here-----------------------------------------------------
int main(int argc, char* argv[])
{
	//cout << "agrc: " << argc;
	string test1="",temp, Prologue="";

	if (argc == 2) // if there is a relative path is given as input
	{
		vector<string> inputfromcommandline;
		inputfromcommandline.assign(argv + 1, argv + argc);
		if ((inputfromcommandline[0].find(".xml") != string::npos) || (inputfromcommandline[0].find(".txt") != string::npos))
		{
			ifstream readFile(inputfromcommandline[0]);
			if (!readFile.is_open())
			{
				cout << "cannot open file ...." << endl;
			}
			while (getline(readFile, temp))
			{
				test1 += temp;
			}
			cout << "xml output read from a file:" << endl;
			cout << test1 << endl;
			cout << endl;
			cout << endl;
		}
	}
	else // xml string hardcoded
	{
		Prologue = "<?xml version=\"1.0\" encoding=\"utf-8\"?><!-- top level comment --><?ProcIns patt1=\"Proval1\" patt2=\"Proval2\"?>";
		test1 = Prologue;
		test1 += "<parent att1='val1' att2='val2'>Parent Text Element<child1 /><child2 sri='dhar' sree='ram' jothi='mathi'>child2 body<child1 /></child2></parent>";
		cout << "xml string from code area\n";
		cout << test1;
	}
	
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	XmlDocument Xmldoc;
	sPtr docelem = Xmldoc.GenerateTree(test1);
	cout << "The xml output after the Tree is Build\n";
	DisplayPackage disp;
	disp.Display(docelem);
	

	cout << "\n\n -----------------------------  DEMONSTRATING REQUIREMENT 4  --------------------------------------" << endl;
	cout << "\n\n -----------------------------  DEMONSTRATING REQUIREMENT 4 Part a  --------------------------------------" << endl;
	cout << "\nMove Contruction being called  : \n";
	TaggedElement tag(move(Xmldoc.moveTaggedElements_requirement()));
	

	cout << "\n\n -----------------------------  DEMONSTRATING REQUIREMENT 4 Part b  --------------------------------------" << endl;
	TaggedElement newtag1("Professor");
	std::vector<std::string>newElementAttributes1 = { "Name", "Jim Fawcett", "School", "Syracuse University" };
	for (size_t i = 0; i < newElementAttributes1.size(); i += 2)
		newtag1.addAttrib(newElementAttributes1[i], newElementAttributes1[i + 1]);

	TaggedElement newtag2("Student");
	std::vector<std::string>newElementAttributes2 = { "Name", "Sridhar Ganapathy", "Sex", "Male" };
	for (size_t i = 0; i < newElementAttributes2.size(); i += 2)
		newtag2.addAttrib(newElementAttributes2[i], newElementAttributes2[i + 1]);

	cout << "Before calling move :" << newtag1.toString() << endl;
	newtag1 = move(newtag2);
	cout << "After calling move assignment operation  :" << newtag1.toString() << endl;


	cout << "\n-----------------------------------<REQUIREMENT 5>----------------------------------------------";
	cout << "\nThe attribute name to be searched for sri\n";
	string Attribute = "sri";
	sPtr PointerforAttribute;
	PointerforAttribute = Xmldoc.DFSSearchTree_forAttribute(docelem, Attribute);
	disp.Display(PointerforAttribute);
	cout << "\n-----------------------------------<REQUIREMENT 6>----------------------------------------------";
	cout << "\n-------------------------capability to find a collection of elements that have a specified tag------------------";
	std::vector<std::shared_ptr<AbstractXmlElement>> vectorpointers;
	cout << "\nThe search for the tag element is child2";
	vectorpointers = Xmldoc.DFSSearchTree_vectoroftag(docelem, "child2");
	cout << "\n Below is the content present in the vector of pointer elements";
	for (auto tmp : vectorpointers)
		disp.Display(tmp);
	cout << "\n------------------------------------<REQUIREMENT 7>------------------------------------------------";
	cout << "\n--------------------Add the child Element by parent tag name---------------------------------------------------";
	cout << "\nParent Tag name: child2\n";
	cout << "Child Tag name: child3\n";
	cout << "Child Tag attribute name: att3\n";
	cout << "Child Tag attribute value: val3\n";
	if (Xmldoc.DFSSearchTree_toaddchild(docelem, "child2", "child3", "att3", "val3", "My name is child3") == true)
		cout << "The Child has been Successfully added\n";
	else
		cout << "Child cannot be added for this tag\n";
	cout << "The below output is seen after adding the new child: child3\n";
	disp.Display(docelem);
	cout << "\n------------------------------------<REQUIREMENT 7>--------------------------------------------------------------";
	cout << "\n--------------------Remove the child Element by parent tag name---------------------------------------------------";
	cout << "\nThe Parent tag from which the child is to be removed is: parent";
	cout << "\nThe child tag to be removed is: child2\n ";
	if (Xmldoc.DFSSearchTree_toremovechild(docelem, "parent", "child2") == true)
		cout << "The Child has been Successfully removed\n";
	else
		cout << "Child cannot be removed for this tag\n";
	cout << "The below output is seen after removing the child: child2\n";
	disp.Display(docelem);
	cout << "\n------------------------------------<REQUIREMENT 7>--------------------------------------------------------------";
	cout << "\n--------------------Add the child Element by attribute name---------------------------------------------------";
	cout << "\nThe parent attribute for which the child has to be added: att1";
	cout << "\nChild Tag element name: child4";
	cout << "\nChild Tag element attribute: att4";
	cout << "\nChild Tag element attribute value: val4";
	if (Xmldoc.DFSSearchTree_addchildbyattribute(docelem, "att1", "child4", "att4", "val4", "My name is child4") == true)
		cout << "The Child has been Successfully added\n";
	else
		cout << "Child cannot be added for this tag\n";
	cout << "The below output is seen after adding the new child: child4\n";
	disp.Display(docelem);
	cout << "\n------------------------------------<REQUIREMENT 7>--------------------------------------------------------------";
	cout << "\n--------------------Remove the child Element by attribute name---------------------------------------------------";
	cout << "\nThe parent attribute for which the child has to be removed: att1";
	cout << "\nChild Tag element name: child4\n";
	cout << "\nChild Tag element attribute: att1\n";
	if (Xmldoc.DFSSearchTree_removechildbyattribute(docelem, "att1", "child4") == true)
		cout << "\nThe Child has been Successfully removed";
	else
		cout << "\nChild cannot be removed for this tag";
	disp.Display(docelem);
	cout << "\n------------------------------------<REQUIREMENT 7>--------------------------------------------------------------";
	cout << "\n--------------------Add a root element to an Empty document tree--------------------------------------------------";
	sPtr EmptydocElement = makeDocElement();
	sPtr NewRootElement = makeTaggedElement("Root");
	NewRootElement->addAttrib("AttributeforRoot", "Val1");
	NewRootElement->addChild(makeTextElement("This is a new root"));
	EmptydocElement->addChild(NewRootElement);
	cout << "\nA root Element is added to an Empty document tree";
	disp.Display(EmptydocElement);
	cout << "\n------------------------------------<REQUIREMENT 8>--------------------------------------------------------------";
	cout << "\n------------------------Return a vector of attributes for a pointer to an element --------------------------------------------------";
	//PointerforAttribute
	cout << "\nBelow is the content to an tag element for which teh attributes need to be found\n";
	disp.Display(PointerforAttribute);
	std::vector<std::pair<std::string, std::string>> AttributeVector;
	AttributeVector = Xmldoc.DFSSearchTree_getvectorofattributes(PointerforAttribute);
	cout << "\nDisplaying below the name-value pairs of all the attributes present in the vector: \n";
	for (auto tmp : AttributeVector)
		cout << "Name: " << tmp.first.c_str() << " Value: " << tmp.second.c_str() << "\n";
	cout << "\n------------------------------------<REQUIREMENT 8>--------------------------------------------------------------";
	cout << "\n------------------------Return a vector of children for a specified element --------------------------------------------------";
	cout << "\nBelow is the content to an tag element for which teh attributes need to be found";
	disp.Display(PointerforAttribute);
	std::vector<std::shared_ptr<AbstractXmlElement>> VectorofChildren1;
	VectorofChildren1 = Xmldoc.DFSSearchTree_getvectorofchildren(PointerforAttribute);
	cout << "\nDisplaying below the children present in the vector for a specified element pointer: \n";
	for (auto tmp : VectorofChildren1)
	{
		cout << "Child: ";
		disp.Display(tmp);
		cout << "\n";
	}
	cout << "\n------------------------------------<REQUIREMENT 9>--------------------------------------------------------------";
	cout << "\n------------------------providing the ability to add an attribute name-value pair --------------------------------------------------";
	// with the 
	string Parent = "parent";
	string Attributename = "type";
	string Attributevalue = "modern";
	if (Xmldoc.DFSSearchTree_addAttribute(docelem, Parent, Attributename, Attributevalue) == true)
		cout << "\nThe Attribute name-value pair has been Successfully removed";
	else
		cout << "\nAttribute name-value pair cannot be added for this tag";
	cout << "\nThe below output is seen after adding the new attribute name-value pair: \n";
	disp.Display(docelem);
	cout << "\n------------------------------------<REQUIREMENT 9>--------------------------------------------------------------";
	cout << "\n------------------------providing the ability to remove an attribute name-value pair --------------------------------------------------";
	// with the 
	string Parent1 = "parent";
	string Attributename1 = "type";
	cout << "\nThe Attribute to be removed: type";
	if (Xmldoc.DFSSearchTree_toremoveAttribute(docelem, Parent1, Attributename1) == true)
		cout << "\nThe Attribute name-value pair has been Successfully removed";
	else
		cout << "\nAttribute name-value pair cannot be removed for this tag";
	cout << "\nThe below output is seen after removing the attribute name-value pair: \n";
	disp.Display(docelem);
	return 0;
}

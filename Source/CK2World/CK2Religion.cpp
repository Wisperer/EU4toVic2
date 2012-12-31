#include "CK2Religion.h"
#include "../Parsers/Object.h"


map<string, CK2Religion*> CK2Religion::all_religions;


void CK2Religion::parseReligions(Object* obj)
{
	vector<Object*> groups = obj->getLeaves();
	for (vector<Object*>::iterator groupsItr = groups.begin(); groupsItr < groups.end(); groupsItr++)
	{
		vector<Object*> religions = (*groupsItr)->getLeaves();
		string group = (*groupsItr)->getKey();
		for (vector<Object*>::iterator religionsItr = religions.begin(); religionsItr < religions.end(); religionsItr++)
		{
			CK2Religion* religion = new CK2Religion((*religionsItr), group);
			all_religions[religion->name] = religion;
		}
	}
}


CK2Religion::CK2Religion(Object* obj, string _group)
{
	group = _group;
	name = obj->getKey();

	vector<Object*> parentObjs = obj->getValue("parent");
	if (parentObjs.size() > 0)
	{
		parent = parentObjs[0]->getLeaf();
	}
}


// e.g. catholic <-> catholic
bool CK2Religion::isSameReligion(const CK2Religion* other) const
{
	if (name == other->name)
		return true;

	return false;
}


// e.g. cathar <-> catholic
bool CK2Religion::isHereticTo(const CK2Religion* other) const
{
	// same religion == no heresy
	if (isSameReligion(other))
		return false;

	// same parent, my child, or my parent == heresy
	if (parent == other->name || name == other->parent || parent == other->parent)
		return true;

	return false;
}


// e.g. orthodox <-> catholic
bool CK2Religion::isRelatedTo(const CK2Religion* other) const
{
	// not the same religion
	if (isSameReligion(other))
		return false;

	// not a heretic
	if (isHereticTo(other))
		return false;

	// but in the same group
	if (group == other->group)
		return true;

	return false;
}


// e.g. sunni <-> catholic
bool CK2Religion::isInfidelTo(const CK2Religion* other) const
{
	// different religious groups == infidel
	if (group != other->group)
		return true;

	return false;
}


CK2Religion* CK2Religion::getReligion(string name)
{
	map<string, CK2Religion*>::iterator itr = all_religions.find(name);
	if (itr == all_religions.end())
		return NULL;

	return itr->second;
}

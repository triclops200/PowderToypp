/*
 * TagsModel.cpp
 *
 *  Created on: Mar 5, 2012
 *      Author: Simon
 */

#include "TagsModel.h"
#include "TagsView.h"
#include "client/Client.h"

TagsModel::TagsModel():
	save(NULL)
{
	// TODO Auto-generated constructor stub

}

void TagsModel::SetSave(Save * save)
{
	this->save = save;
	notifyTagsChanged();
}

Save * TagsModel::GetSave()
{
	return save;
}

void TagsModel::RemoveTag(string tag)
{
	if(save)
	{
		std::vector<string> * tags = Client::Ref().RemoveTag(save->GetID(), tag);
		if(tags)
		{
			save->SetTags(vector<string>(*tags));
			notifyTagsChanged();
			delete tags;
		}
		else
		{
			lastError = Client::Ref().GetLastError();
			notifyError();
		}
	}
}

void TagsModel::AddTag(string tag)
{
	if(save)
	{
		std::vector<string> * tags = Client::Ref().AddTag(save->GetID(), tag);
		if(tags)
		{
			save->SetTags(vector<string>(*tags));
			notifyTagsChanged();
			delete tags;
		}
		else
		{
			lastError = Client::Ref().GetLastError();
			notifyError();
		}
	}
}

void TagsModel::AddObserver(TagsView * observer)
{
	observers.push_back(observer);
	observer->NotifyTagsChanged(this);
}

void TagsModel::notifyTagsChanged()
{
	for(int i = 0; i < observers.size(); i++)
	{
		observers[i]->NotifyTagsChanged(this);
	}
}

void TagsModel::notifyError()
{
	for(int i = 0; i < observers.size(); i++)
	{
		observers[i]->NotifyError(this);
	}
}

TagsModel::~TagsModel() {
	// TODO Auto-generated destructor stub
}

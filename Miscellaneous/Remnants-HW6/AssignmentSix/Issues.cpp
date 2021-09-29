// Mine

MovieNodeLL* LL_remove( MovieNodeLL* head, std::string title ) // Works
{
	if ( head )
	{
		MovieNodeLL* tmpNode;
		
		if ( head->title == title ) // If removing head
		{
			tmpNode = head->next;
			delete head;
			return tmpNode;
		}

		for ( MovieNodeLL* currentNode = head; currentNode->next != nullptr; currentNode = currentNode->next )
		{
			if ( currentNode->next->title == title )
			{
				tmpNode = currentNode->next;
				currentNode->next = currentNode->next->next;
				delete tmpNode;
				tmpNode = currentNode;
				return head;
			}
		}
		return nullptr;
	}
	else
	{
		return nullptr;
	}
}
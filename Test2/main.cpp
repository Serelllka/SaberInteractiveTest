#include <iostream>
#include <map>

struct ListNode
{
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
    ListNode* rand = nullptr;
    std::string data;
};

class List
{
public:
    void Serialize(FILE* file);
    void Deserialize(FILE* file);

    void push_front(ListNode* node);
    void push_back(ListNode* node);

    ~List();
private:
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    int count = 0;
};

void List::push_front(ListNode* node)
{
    if (count == 0)
    {
        head = node;
        tail = node;
    }
    else
    {
        node->next = head;
        head->prev = node;
        head = node;
    }
    ++count;
}

void List::push_back(ListNode* node)
{
    if (count == 0)
    {
        head = node;
        tail = node;
    }
    else
    {
        node->prev = tail;
        tail->next = node;
        tail = node;
    }
    ++count;
}

List::~List()
{
    auto ptr = head;
    while(ptr != nullptr)
    {
        ListNode * tmp = ptr->next;
        delete ptr;
        ptr = tmp;
    }
}

void List::Serialize(FILE *file)
{
    fwrite(&count, sizeof(count), 1, file);
    ListNode * ptr = head;
    for (int i = 0; i < count; ++i)
    {
        fwrite(&ptr, sizeof(ptr), 1, file);
        fwrite(&ptr->prev, sizeof(ptr->prev), 1, file);
        fwrite(&ptr->next, sizeof(ptr->next), 1, file);
        fwrite(&ptr->rand, sizeof(ptr->rand), 1, file);
        auto dataSize = ptr->data.size();
        fwrite(&dataSize, sizeof(dataSize), 1, file);
        fprintf(file, "%s", ptr->data.data());
        ptr = ptr->next;
    }
}

void List::Deserialize(FILE *file)
{
    count = 0;
    int newCount;
    std::map<ListNode*, std::pair<ListNode*, ListNode*>> mp;
    fread(&newCount, sizeof(newCount), 1, file);
    for (int i = 0; i < newCount; ++i)
    {
        ListNode *ptr, *pptr, *nptr, *rptr;
        std::string::size_type dataSize;
        fread(&ptr, sizeof(ptr), 1, file);
        fread(&pptr, sizeof(pptr), 1, file);
        fread(&nptr, sizeof(nptr), 1, file);
        fread(&rptr, sizeof(rptr), 1, file);

        fread(&dataSize, sizeof(dataSize), 1, file);
        char text[dataSize];

        fread(text, sizeof(char), dataSize, file);
        auto* tmp = new ListNode{nullptr, nullptr, nullptr, text};
        push_back(tmp);
        mp.insert(std::make_pair(tmp, std::make_pair(ptr, rptr)));
    }

    for (auto & it : mp)
    {
        if (it.second.second != nullptr)
        {
            for (auto &it2 : mp)
            {
                if (it2.second.first == it.second.second)
                {
                    it.first->rand = it2.first;
                }
            }
        }
    }
}

int main()
{
    List list;
    FILE* output = fopen("input.txt", "wb");

    auto node1 = new ListNode;
    node1->data = "data1";
    auto node2 = new ListNode;
    node2->data = "data2";
    auto node3 = new ListNode;
    node3->data = "data3";
    auto node4 = new ListNode;
    node4->data = "data4";
    node2->rand = node1;
    node4->rand = node2;
    list.push_back(node1);
    list.push_back(node2);
    list.push_back(node3);
    list.push_back(node4);
    list.Serialize(output);
    fclose(output);



    List newList;
    FILE* input = fopen("input.txt", "rb");
    newList.Deserialize(input);
    fclose(input);

}
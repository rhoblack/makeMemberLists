#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#define MAX_MEMBER_COUNT 10000

struct MemberInfo_t
{
    int id;
    char name[21];
    char address[20];
    uint8_t cardNum[5];
};

void MakeMembers()
{
    MemberInfo_t seoulTechMember;

    srand(time(NULL));

    FILE *fpList;
    fpList = fopen("memberLists.txt", "w");
    FILE *fpList2;
    fpList2 = fopen("memberLists.bin", "w");

    for (int id = 0; id < MAX_MEMBER_COUNT; id++)
    {
        seoulTechMember.id = id;

        for (int i = 0; i < 20; i++)
        {
            seoulTechMember.name[i] = rand() % 26 + 'a';
        }
        seoulTechMember.name[20] = '\0';

        sprintf(seoulTechMember.address, "%02ddong-%03dho", rand() % 100, rand() % 1000);

        for (int i = 0; i < 5; i++)
        {
            seoulTechMember.cardNum[i] = rand() % 0xff;
        }
        fprintf(fpList, "%05d %s %s %03d-%03d-%03d-%03d-%03d\n",
                seoulTechMember.id,
                seoulTechMember.name,
                seoulTechMember.address,
                seoulTechMember.cardNum[0],
                seoulTechMember.cardNum[1],
                seoulTechMember.cardNum[2],
                seoulTechMember.cardNum[3],
                seoulTechMember.cardNum[4]);

        fwrite(&seoulTechMember, sizeof(seoulTechMember), 1, fpList2);
    }
    fclose(fpList);
    fclose(fpList2);
}

bool cardCompare(MemberInfo_t a, MemberInfo_t b)
{
    if (!memcmp(a.cardNum, b.cardNum, sizeof(a.cardNum)))
    {
        return strcmp(a.name, b.name) < 0 ? true : false;
        // return a.name < b.name;
    }
    else
    {
        return (memcmp(a.cardNum, b.cardNum, sizeof(a.cardNum)) < 0) ? true : false;
    }
}

bool nameCompare(MemberInfo_t a, MemberInfo_t b)
{
    if (!memcmp(a.name, b.name, sizeof(a.cardNum)))
    {
        //return strcmp(a.name, b.name) < 0 ? true : false;
         return a.id < b.id;
    }
    else
    {
        return (memcmp(a.name, b.name, sizeof(a.name)) < 0) ? true : false;
    }
}

void ReadnSort()
{
    MemberInfo_t tempMember;
    std::vector<MemberInfo_t> vecMemList;

    FILE *fpReadMembers;
    FILE *fpWriteMembers;
    fpReadMembers = fopen("memberLists.bin", "r");
    fpWriteMembers = fopen("sortMemberLists.txt", "w");

    while (fread(&tempMember, sizeof(MemberInfo_t), 1, fpReadMembers))
    {
        vecMemList.push_back(tempMember);
    }

    std::sort(vecMemList.begin(), vecMemList.end(), nameCompare);
    for (const auto &mem : vecMemList)
    {
        fprintf(fpWriteMembers, "%05d %s %s %03d-%03d-%03d-%03d-%03d\n",
                mem.id,
                mem.name,
                mem.address,
                mem.cardNum[0],
                mem.cardNum[1],
                mem.cardNum[2],
                mem.cardNum[3],
                mem.cardNum[4]);
    }

    fclose(fpReadMembers);
    fclose(fpWriteMembers);
}

int main()
{
    //MakeMembers();
    //ReadnSort();
    //154-140-140-213-203
    uint8_t card[5] = {154,140,140,213,203};

    MemberInfo_t tempMember;
    std::vector<MemberInfo_t> vecMemList;

    FILE *fpReadMembers;
    fpReadMembers = fopen("memberLists.bin", "r");
    
    while (fread(&tempMember, sizeof(MemberInfo_t), 1, fpReadMembers))
    {
        vecMemList.push_back(tempMember);
    }

    for (long unsigned int i=0; i<vecMemList.size(); i++) {
        if (!memcmp(vecMemList[i].cardNum, card, sizeof(card))) {
            printf("%05d %s %s %03d-%03d-%03d-%03d-%03d\n",
                vecMemList[i].id,
                vecMemList[i].name,
                vecMemList[i].address,
                vecMemList[i].cardNum[0],
                vecMemList[i].cardNum[1],
                vecMemList[i].cardNum[2],
                vecMemList[i].cardNum[3],
                vecMemList[i].cardNum[4]);
        }
    }


    fclose(fpReadMembers);

    return 0;
}
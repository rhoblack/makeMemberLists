#include <iostream>

struct MemberInfo_t
{
    int id;
    char name[21];
    char address[20];
    int cardNum[5];
};

int main()
{
    MemberInfo_t seoulTechMember;
    srand(time(NULL));
    std::cout << "Hello World!\n";

    FILE *fpList;
    fpList = fopen("memberLists.txt", "w+");
    FILE *fpList2;
    fpList2 = fopen("memberLists.bin", "w+");

    for (int id = 0; id < 10000; id++)
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
    // std::cout << seoulTechMember.id
    //           << seoulTechMember.name
    //           << seoulTechMember.address
    //           << seoulTechMember.cardNum[0]
    //           << std::endl;
    fclose(fpList);
    return 0;
}
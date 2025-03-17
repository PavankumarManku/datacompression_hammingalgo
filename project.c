#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max 1000
struct name{
    // For PlayList Number
    int number;
    // For PlayList Name
    char c[100];
};
struct name * playListDetails[max];
struct node{
    char songName[100];
    struct node * pre,*next;
};
void clearInputBuffer();
void mainMenu(int s);
void showPlayList(int s);
struct node * addSongs(struct node * p,char * n);
struct node * deleteSongs(struct node * p,char * n);
void playSong(struct node * head);
void PlayListSongs(struct node * p,int s);
int main(){
    // size will keep track no. of playlist in the music player
    int size = 0;
    struct node * playlist[max];
    for(int i=0;i<max;i=i+1){
        playListDetails[i] = (struct name *)malloc(sizeof(struct name));
    }
    for(int i=0;i<max;i=i+1){
        playlist[i] = NULL;
    }
    printf("------------------------------------------> MUSIC PLAYER <------------------------------------------\n\n");
    playListDetails[size]->number = size;
    strcpy(playListDetails[size]->c,"Liked Songs");
    playlist[size] = addSongs(playlist[size],"Ordinary Person");
    playlist[size] = addSongs(playlist[size],"LokiVerse");
    playlist[size] = addSongs(playlist[size],"Rolex BGM");
    size = size + 1;
    playListDetails[size]->number = size;
    strcpy(playListDetails[size]->c,"Prabhas");
    playlist[size] = addSongs(playlist[size],"JaiShreeRam");
    playlist[size] = addSongs(playlist[size],"Saahore Bahubali");
    playlist[size] = addSongs(playlist[size],"Chatrapathi");
    playlist[size] = addSongs(playlist[size],"Yahoo Yahoo");
    size = size + 1;
    playListDetails[size]->number = size;
    strcpy(playListDetails[size]->c,"Anirudh OST");
    playlist[size] = addSongs(playlist[size],"Kaththi Theme");
    playlist[size] = addSongs(playlist[size],"Bhavani Theme");
    playlist[size] = addSongs(playlist[size],"Master Coming");
    playlist[size] = addSongs(playlist[size],"3 BGM");
    playlist[size] = addSongs(playlist[size],"Rolex BGM");
    size = size + 1;
   // PlayListSongs(playlist[1],1);
   int x;
   while(1){
    mainMenu(size);
    printf("ENTER RESPECTIVE FOR SPECIFIC FUNCTION IN THE MUSIC PLAYER : ");
    scanf("%d",&x);
    clearInputBuffer();
    if(x == 1){
        playListDetails[size]->number = size;
        printf("Enter the Name of the new PlayList : ");
        scanf("%100[^\n]",playListDetails[size]->c);
        char ch[10],nm[100];
        while(1){
            printf("Do u want add songs/music into this playlist : ");
            scanf("%s",ch);
            clearInputBuffer();
            if(strcmp(ch,"yes")==0||strcmp(ch,"YES")==0||strcmp(ch,"Yes")==0){
                printf("Enter the name of the song u want to add into this playlist : ");
                scanf("%100[^\n]",nm);
                playlist[size] = addSongs(playlist[size],nm);
            }
            else{
                printf("New PlayList %s Added\n\n",playListDetails[size]->c);
                break;
            }
        }
        size = size + 1;
    }
    else if(x == 2){
        char ch[100];
        printf("Enter the PlayList Name to add new Songs/Music :");
        scanf("%100[^\n]",ch);
        clearInputBuffer();
        int y = -1;
        for(int i=0;i<size;i=i+1){
            if(strcmp(ch,playListDetails[i]->c)==0){
                y = playListDetails[i]->number;
                break;
            }
        }
        if(y != -1){
            printf("\n");
            PlayListSongs(playlist[y],y);
            do{
                printf("Enter the name of the song u want to add into the playlist : ");
                scanf("%100[^\n]",ch);
                clearInputBuffer();
                playlist[y] = addSongs(playlist[y],ch);
                printf("Do u want to add some more songs? If so enter Yes : ");
                scanf("%10[^\n]",ch);
                clearInputBuffer();
            }while(strcmp(ch,"Yes")==0||strcmp(ch,"yes")==0||strcmp(ch,"YES")==0);
            printf("PLAY LIST -> %s <- UPDATED\n",playListDetails[y]->c);
            PlayListSongs(playlist[y],y);
        }
        else{
            printf("PLAY LIST NOT FOUND...! TRY AGAIN\n");
        }
    }
    else if(x == 3){
        char ch[100];
        printf("Enter the PlayList Name to Delete Specific Songs/Music :");
        scanf("%100[^\n]",ch);
        clearInputBuffer();
        int y = -1;
        for(int i=0;i<size;i=i+1){
            if(strcmp(ch,playListDetails[i]->c)==0){
                y = playListDetails[i]->number;
                break;
            }
        }
        if(y != -1){
            printf("\n");
            PlayListSongs(playlist[y],y);
            do{
                printf("Enter the name of the song u want to Delete From the playlist : ");
                scanf("%100[^\n]",ch);
                clearInputBuffer();
                playlist[y] = deleteSongs(playlist[y],ch);
                printf("Do u want to Delete some more songs? If so enter Yes : ");
                scanf("%10[^\n]",ch);
                clearInputBuffer();
            }while(strcmp(ch,"Yes")==0||strcmp(ch,"yes")==0||strcmp(ch,"YES")==0);
            printf("PLAY LIST -> %s <- UPDATED\n",playListDetails[y]->c);
            PlayListSongs(playlist[y],y);
        }
        else{
            printf("PLAY LIST NOT FOUND...! TRY AGAIN\n");
        }
    }
    else if(x == 4){
        char ch[100];
        printf("Choose a PlayList to play Songs/Music :");
        scanf("%100[^\n]",ch);
        clearInputBuffer();
        int y = -1;
        for(int i=0;i<size;i=i+1){
            if(strcmp(ch,playListDetails[i]->c)==0){
                y = playListDetails[i]->number;
                break;
            }
        }
        if(y != -1){
            printf("\n");
            PlayListSongs(playlist[y],y);
            printf("Enter the name of the song/music u want to play : ");
            scanf("%100[^\n]",ch);
            clearInputBuffer();
            struct node * q = playlist[y],*p;
            while(q != NULL){
                if(strcmp(q->songName,ch)==0){
                    break;
                }
                q = q->next;
            }
            if(q != NULL){
                playSong(q);
            }
            else{
                printf("SONG NOT PRESENT IN THE PLAYLIST\n");
            }
        }
        else{
            printf("PLAY LIST NOT FOUND...! TRY AGAIN\n");
        }
    }
    else if(x == 5){
        char ch[100];
        printf("Enter the PlayList Name to Delete it :");
        scanf("%100[^\n]",ch);
        clearInputBuffer();
        int y = -1;
        for(int i=0;i<size;i=i+1){
            if(strcmp(ch,playListDetails[i]->c)==0){
                y = playListDetails[i]->number;
                break;
            }
        }
        if(y != -1){
            size = size - 1;
            for(int i=y;i<size;i=i+1){
                playListDetails[i] = playListDetails[i+1];
                playlist[i] = playlist[i+1];
            }
        }
        else{
            printf("PLAY LIST NOT FOUND...! TRY AGAIN\n");
        }
    }
    else if(x == 6){
        printf("-------------------*** THANK YOU FOR USING THE MUSIC PLAYER ***-------------------");
        break;
    }
    else{
        printf("\n***** INVALID SELECTION...! TRY AGAIN *****\n");
    }
   }
}
void clearInputBuffer(){
    char c;
    while((c=getchar())!='\n' && c!=EOF){
        //Keep reading and discarding characters until a newline or EOF is encountered
    }
}
struct node * addSongs(struct node * p,char * n){
    if(p == NULL){
        struct node * newnode = (struct node *)malloc(sizeof(struct node));
        newnode->pre = newnode->next = NULL;
        strcpy(newnode->songName,n);
        return newnode;
    }
    else{
        struct node * q = p;
        while(q->next != NULL){
            q = q->next;
        }
        struct node * newnode = (struct node *)malloc(sizeof(struct node));
        q->next = newnode;
        newnode->next = NULL;
        newnode->pre = q;
        strcpy(newnode->songName,n);
        return p;
    }
}
void PlayListSongs(struct node * p,int s){
    printf("------------------------------------------PLAY-LIST : %s ------------------------------------------\n",playListDetails[s]->c);
    struct node * q = p;
    printf("\nLIST OF SONGS\n\n");
    while(q != NULL){
        printf("-> %s\n",q->songName);
        q = q->next;
    }
}
void showPlayList(int s){
    printf("----------- EXISISTING PLAY LISTS IN THE MUSIC PLAYER -----------\n");
    for(int i=0;i<s;i=i+1){
        printf("-> %s\n",playListDetails[i]->c);
    }
    printf("----------------------------------------------------------------------------\n");
    printf("\n");
}
void mainMenu(int s){
    printf("\n----------- EXISISTING PLAY LISTS IN THE MUSIC PLAYER -----------\n");
    for(int i=0;i<s;i=i+1){
        printf("-> %s\n",playListDetails[i]->c);
    }
    printf("--------------------------------------------\n");
    printf("* DO YOU WANT TO CREATE A NEW PLAYLIST AND ADD SONGS/MUSIC? IF SO ENTER 1\n\n");
    printf("* DO YOU WANT TO ADD SONGS/MUSIC INTO A EXISISTING PLAYLIST? IF SO ENTER 2\n\n");
    printf("* DO YOU WANT TO DELETE SONGS/MUSIC IN A EXISISTING PLAYLIST? IF SO ENTER 3\n\n");
    printf("* DO YOU WANT TO PLAY ANY SONG/MUSIC IN ANY SPECIFIC PLAYLIST? IF SO ENTER 4\n\n");
    printf("* DO YOU WANT TO DELETE ANY EXISISTING PLAYLIST IN THE MUSIC PLAYER? IF SO ENTER 5\n\n");
    printf("* DO YOU WANT TO EXIT FROM THE MUSIC PLAYER? IF SO ENTER 6\n");
    printf("----------------------------------------------------------------------------\n\n");
}
struct node * deleteSongs(struct node *p,char * n){
    if(strcmp(p->songName,n)==0){
        struct node * q = p;
        q = q->next;
        q->pre = NULL;
        return q;
    }
    struct node * r = p;
    struct node * s;
    while(r->next != NULL){
        s = r;
        r = r->next;
    }
    if(strcmp(r->songName,n)==0){
        s->next = NULL;
        free(r);
        return p;
    }
    else{
        struct node * q = p;
        struct node * t;
        while(strcmp(q->songName,n)!=0){
            t = q;
            q = q->next;
        }
        struct node * u = q->next;
        t->next = u;
        u->pre = t;
        free(q);
        return p;
    }
    printf("No song Available like that\n\n");
    return p;
}
void playSong(struct node * p){
    static int z = -1;
    if(p == NULL || z == 0){
        return;
    }
    int n;
    printf("\n\t\t\t\t\t\t  %s\n",p->songName);
    printf("-----------------------------------------------------> || <-----------------------------------------------------\n");
    printf("\n------------------------------------------ OPTIONS AVAILABLE HERE ----------------------------------------------");
    printf("\nFor Previous Track Enter 1 ------------------------------------------------ For Next Track Enter 2\n");
    printf("                       For Stoping the play and Exiting the Current Playlist Enter 0\n");
    printf("--------------------------------------------------------------------------------------------\n");
    printf("\nEnter Your Option : ");
    scanf("%d",&n);
    if(n == 1){
        p = p->pre;
        playSong(p);
    }
    else if(n == 2){
        p = p->next;
        playSong(p);
    }
    else if(n == 0){
        z = 0;
    }
}
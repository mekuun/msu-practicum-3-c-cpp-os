#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

struct one_node {
    struct one_node *left, *right;
    char *word;
    struct posit_i *info;
    struct posit **pos;
};
enum modes {X, R, S};

struct posit {long x, y;}; //coord
struct posit_i {long ap, alp;};


struct one_node *new_node(char *word, struct posit *pos) {
    struct one_node *node = (struct one_node*) malloc(sizeof(struct one_node));
    if (!node) return NULL;
    node -> pos=(struct posit **)malloc(sizeof(struct posit *));
    if (!node->pos) return NULL;
    node -> info=(struct posit_i *)malloc(sizeof(struct posit_i));
    if (!node->info) return NULL;


    if ((!node) || (!node -> pos) || (!node -> info)) {
        fprintf(stderr, "Unknown error\n");
        exit(1);
    }
//first elem
    *(node -> pos)=pos;
    node -> info -> alp = 1;
    node -> info -> ap = 1;
    node -> right = NULL;
    node -> left = NULL;
    node -> word = word;


    return node;
}

int is_divider(char cur){
    if ((cur == ';') || (cur == ',') || (cur == '.') || (cur == ' ') || (cur == '-') || (cur == ':') || (cur == '(') || (cur == ')') || (cur =='\n')) return 1;
    return 0;
}

void append_node(struct one_node *tree, char *new_word, struct posit *add_pos){
    if(!strcmp(tree -> word, new_word)) {
        if(tree -> info -> ap == tree -> info -> alp){
            tree -> pos = (struct posit **)realloc(tree -> pos, 4 * (tree -> info -> alp) * sizeof(struct posit *));
            if (!tree->pos) return;
            tree -> info -> alp *=4;
        }
        (tree -> pos)[tree -> info -> ap ++]=add_pos;
        return;
    }
    else if(strcmp(tree -> word, new_word) > 0) {
        if (!(tree -> left)) {
            tree -> left = new_node(new_word, add_pos);
            return;
        }
        else append_node(tree->left, new_word, add_pos);
    }

    else if(strcmp(tree->word, new_word) < 0){

        if (!tree -> right) {
            tree -> right= new_node(new_word, add_pos);
            return;
        }
        else append_node(tree->right, new_word, add_pos);
    }
}


struct one_node *build_tree(int fd){
    struct one_node *tree = NULL;
    struct posit *new_pos;

    long long int x = 1, y = 1, i=0, sizeof_str=0;
//    x = y = 0;
    char cur='\0', *cur_word=NULL;
    int div;
    int buf;
    while((buf = read(fd, &cur, sizeof(char))) > 0 ){
        i++;
        div = is_divider(cur);
        if (cur_word && div){
            new_pos=(struct posit *)malloc(sizeof(struct posit));
            if (!new_pos) return NULL;
            new_pos-> y = y;
            new_pos-> x = x;
            if (!tree) tree = new_node(cur_word, new_pos);
            else append_node(tree, cur_word, new_pos);
            cur_word = NULL;
        }

        if (cur == '\n') {x++; i = 0; y = 1;}
        if(div) continue;
        if(!cur_word) {
            cur_word = (char *) malloc(4 * sizeof(char));
            if (!cur_word) return NULL;
            *(cur_word) = '\0';
            sizeof_str = 4;
            y = i;
        }
        if((strlen(cur_word) + 1 >= sizeof_str)){
            sizeof_str*=4;
            cur_word=(char *)realloc(cur_word, sizeof_str*sizeof(char));
            if (!cur_word) {fprintf(stderr, "Unknown error"); exit(1);}
            *(cur_word + sizeof_str) = '\0';
        }

        *(cur_word+strlen(cur_word))=cur;
        *(cur_word+strlen(cur_word)+1)='\0';
    }

    //empty file
    if (buf <= 0 && cur == '\0') return NULL;
    return tree;
};


struct one_node *find(struct one_node *tree, char *word){
    if(!strcmp(word, tree->word)) return tree;
    else if(strcmp(word, tree->word)&&!(tree->right)&&!(tree->left)) return NULL;
    else if(strcmp(word, tree->word)>0) {
        if (!tree->right) return NULL;
        else return find(tree->right, word);
    }
    else if(strcmp(word, tree->word)<0) {
        if (!tree->left) return NULL;
        else return find(tree->left, word);
    }
    return NULL;
};

void search(int fd, struct one_node *tree, char *word, long long unsigned int lower, long long unsigned int upper){
    int res, i=0;
    char cur, flag=0;
    struct one_node *node=find(tree, word);
    if (!node) return;
    long long unsigned int str=1, next_str;
    if (lower==1) next_str=(node->pos)[0]->x;
    else {
        while ((i+1<node->info->ap) && (node->pos)[i]->x < lower) i++;
        next_str=(node->pos)[i]->x;
    }

    if (i+1>node->info->ap) return;
    if (next_str<lower) return;
    lseek(fd, 0, SEEK_SET);
    while((res = read(fd, &cur, sizeof(char)) > 0 )&& next_str <= upper){
        if (cur=='\n') {
            str++;
            if (flag){
                write(1, "\n", sizeof(char));
                if (i+1==node->info->ap) return;
                else {
                    while (i+1<node->info->ap && next_str == (node->pos[++i])->x){};
                    next_str=(node->pos[i])->x;
                    flag=0;
                }
            }
            continue;
        }
        if (str==next_str){
            write(1, &cur, sizeof(char));
            flag=1;
        }
    }
};

void replace(int fd, struct one_node *tree, char *word1, char *word2, long long unsigned int lower, long long unsigned int upper){
    char cur, flag=0;
    int res;
    long long unsigned int offset=strlen(word1), symb=0, i=0;
    struct one_node *node=find(tree, word1);
    if (!node) return;
    long long unsigned int str=1, next_str, next_symb;
    if (lower==1) {
        next_str=(node->pos)[0]->x;
        next_symb=(node->pos)[0]->y;
    }
    else {
        while ((i+1<node->info->ap) && (node->pos)[i]->x < lower) i++;
        next_str=(node->pos)[i]->x;
        next_symb=(node->pos)[i]->y;
    }
    if (next_str<lower) return;		//if all occurences are below lower limit
    lseek(fd, 0, SEEK_SET);
    while((res = read(fd, &cur, sizeof(char))) > 0&&str<=upper){
        symb++;
        if (str==next_str&&symb==next_symb) {
            flag=1;
            write(1, word2, strlen(word2)*sizeof(char));
            lseek(fd, (offset-1)*sizeof(char), SEEK_CUR);
            symb+=strlen(word1)-1;
            if (i+1<node->info->ap && (node->pos)[i + 1]->x == str) {
                next_symb=(node->pos)[++i]->y;
                continue;
            }
            else if (i>=node->info->ap) {return;}
        }
        else if(cur=='\n') {
            if (flag) write(1, "\n", sizeof(char));
            if (i+1<node->info->ap && str == next_str){
                next_str=(node->pos)[++i]->x;
                next_symb=(node->pos)[i]->y;
            }
            else if (i>=(node->info->ap)) {write(1, "\n", sizeof(char)); return;} //if +1 doesnt check next lines

            str++;
            flag=0;
            symb=0;
            continue;
        }
        else if (str==next_str) write(1, &cur, sizeof(char));
    }
}

char string_to_int(char *str, long long unsigned int *result){
    long long unsigned int i = 0, n=0;
    char flag=0;
    if (str[0]=='-'){flag=1; i=1;}
    for (; i<strlen(str); i++){
        if (!isdigit(str[i])) return 1;
        n=n*10+str[i]-'0';
    }
    if (flag) {fprintf(stderr, "Incorrect diapason"); exit(1);}
    *result=n;
    return 0;
};

void clear(struct one_node *node){
    int i=0;
    if (!node) return;
    if (node->left||node->right){
        clear(node->left);
        clear(node->right);
    }
    for (i=0; i<node->info->ap; i++){
        free(*(node->pos+i));
    }
    free(node->info);
    free(node->word);
    free(node->pos);
    free(node);
}

int main(int argc, char **argv){

    int finp = open(argv[1], O_RDWR);
    if (finp < 0) {
        fprintf(stderr, "Can't open file %s\n", argv[1]);
        return 1;
    }
    enum modes mode = X;
    int i = 2;
    char *word1 = NULL, *word2 = NULL;
    long long unsigned int from=-1, to=-1;
    while (i < argc){

        if ((!strcmp(argv[i], "-r")||!strcmp(argv[i], "--replace"))&& mode == X) {
            mode = R;
            if (++i < argc) word1 = argv[i];
            else {fprintf(stderr, "Incorrect parameters of command line\n"); return 1;}
            if (++i < argc) word2 = argv[i];
            else {fprintf(stderr, "Incorrect parameters of command line\n"); return 1;}
        }
        else if ((!strcmp(argv[i], "-s")||!strcmp(argv[i], "--search"))&& mode == X) {
            mode = S;
            if(++i < argc) word1 = argv[i];
            else {fprintf(stderr, "Incorrect parameters of command line\n"); return 1;}
        }
        else if(!strcmp(argv[i], "-d")||!strcmp(argv[i], "--diapason")) {
            if (++i>=argc||string_to_int(argv[i], &from)) {fprintf(stderr, "Incorrect parameters of command line\n"); return 1;}
            if (++i>=argc) to=LONG_MAX;
            else if (string_to_int(argv[i], &to)){
                if (!strcmp(argv[i], "-s")||!strcmp(argv[i], "--search")||!strcmp(argv[i], "-r")||!strcmp(argv[i], "--replace")) {continue;}
                fprintf(stderr, "Incorrect parameters of command line\n"); return 1;
            }
        }
        else {fprintf(stderr, "Incorrect parameters of command line\n"); return 1;}
        i++;
    }
    if (from > to) {fprintf(stderr, "Incorrect diapason\n"); return 1;}
    if (from == -1) from = 1;
    if (to <= 0 || from <= 0) {fprintf(stderr, "Incorrect diapason\n"); return 1;}
    if (mode == X) {fprintf(stderr, "Incorrect parameters of command line\n"); return 1;}
    struct one_node *tree;
    tree = build_tree(finp);
    if (!tree) return 1;
    if (mode == R) replace(finp, tree, word1, word2, from, to);
    else if (mode == S) search(finp, tree, word1, from, to);

    clear(tree);


    return 0;
}
#include <stdio.h>

int main(int argc, char **argv)
{
    FILE * p_fw_bin = NULL;
    FILE * p_head_file = NULL;
    unsigned int byte_cnt = 0;
    char *head_name = "Hwfw_88X33x0.h";
    int c = 0;    

    p_fw_bin=fopen(argv[1],"rb");
    if(p_fw_bin==NULL)
    {
	printf("can not open firmware\n");
        return 1;
    }

    p_head_file=fopen(head_name,"w");
    if(p_head_file==NULL)
    {
        printf("can not create head file\n");
        return 1;
    }

    fprintf(p_head_file,"static MTD_U8 _33x0_fw[]={\n");

    c=fgetc(p_fw_bin);
    for(; c!=EOF; byte_cnt++)
    {
        if(byte_cnt!=0)
        {
            fprintf(p_head_file,", ");
	    if(byte_cnt%8==0)
                fprintf(p_head_file,"\n");
        }
        fprintf(p_head_file,"0x%02x", c);
        c=fgetc(p_fw_bin);
    }

    fprintf(p_head_file,"\n};\n#define FW_SIZE %d\n",byte_cnt);
    fprintf(p_head_file, "#define V_MAJ 0\n");
    fprintf(p_head_file, "#define V_MIN 3\n");
    fprintf(p_head_file, "#define V_INC 4\n");
    fprintf(p_head_file, "#define V_TEST 0\n");
    fclose(p_fw_bin);
    fclose(p_head_file);
    return 0;
}
    
     


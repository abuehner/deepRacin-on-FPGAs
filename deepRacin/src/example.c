#include <deepRACIN.h>
#include <stdio.h>
//#include <png.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>


int x, y;

int width = 224;
int height = 224;
//png_byte color_type;
//png_byte bit_depth;

//png_structp png_ptr;
//png_infop info_ptr;
int number_of_passes;
//png_bytep * row_pointers;


// Init libpng and image read buffers
/*void initialize_image_buffer()
{
    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
    for (y=0; y<height; y++)
            row_pointers[y] = (png_byte*) malloc(sizeof(png_bytep) * width * 3);
}

// Read PNG file with libpng
void read_image(char* path)
{
    char png_header[8];
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
    {
        printf("[read_image] read struct failed");
        abort();
    }
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        printf("[read_image] png_create_info_struct failed");
        abort();
    }
    png_set_sig_bytes(png_ptr, 8);
    FILE *fp = fopen(path, "rb");
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        printf("[read_image] init_io failed");
        abort();
    }
    png_init_io(png_ptr, fp);
    if (!fp)
    {
        printf("[read_image] File %s could not be opened.", path);
        abort();
    }
    fread(png_header, 1, 8, fp);
    if (png_sig_cmp(png_header, 0, 8))
    {
        printf("[read_image] File %s is not a PNG file", path);
        abort();
    }


    png_read_info(png_ptr, info_ptr);

    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        printf("[read_png_file] Error during read_image");
        abort();
    }

    png_read_image(png_ptr, row_pointers);
    // strip the alpha channel if existing
    if (color_type & PNG_COLOR_MASK_ALPHA)
    {
        png_set_strip_alpha(png_ptr);
    }
    fclose(fp);
}*/
/*
int main(void)
{

    int i,j;
    int buffersize = width*height*3*sizeof(float);
    float* feed_buffer = malloc(buffersize);



    // Required Pointers and Variables
    dR_Graph* net;
    dR_Node** feedlist;
    dR_Node** nodeslist;
    gint numnodes;
    gint numfeeds;
    dR_Node* lastnode;

    // New deepracin graph    printf("t1\n");

    net = dR_NewGraph();


    // Configure deepracin
    // Do not display debug information
    net->config->debugInfo = FALSE;
    // Profile GPU runtime
    net->config->profilingGPU = FALSE;
    // Profile CPU runtime
    net->config->profilingCPU = TRUE;
    // Give command line output
    net->config->silent = FALSE;
    // No Platform Hint - Choose first GPU available
    net->clConfig->clPlatformName = NULL;

    net->clConfig->clDeviceType = CL_DEVICE_TYPE_ACCELERATOR;
    // Initialize OpenCL
    dR_initCL(net);

    // Load dR Model and get list of nodes and data feed nodes
    dR_loadGraph(net,"squeezenet_whole/",&nodeslist,&numnodes,&feedlist,&numfeeds);
    lastnode = nodeslist[numnodes-1];

    // Mark the output nodes whose output buffers can be fetched with dR_getOutputBuffers
    // Nodes marked as output are guaranteed to have consistent output buffers after using dR_apply()
    dR_setAsOutput(net,lastnode);
   printf("3 \n");

    // Print network to console
    //dR_printNetObject(net, NULL);

    // Prepare network for execution - scheduling, buffer creation, kernel creation is done here
    dR_prepare(net);

    cl_float* odata = (gfloat*)g_malloc(1000*sizeof(gfloat));
    cl_mem* outbuffers[1];

    // Fetch pointers to output buffers
    dR_getOutputBuffers(net,outbuffers);
   // initialize_image_buffer();
    g_print("Start applying graph...\n");
    printf("4 \n");

    for(i=0;i<10;i++)
    {
        // Read and prepare image using OpenCV (does not have to be OpenCV)
        if(i%2==0)
        {
           // read_image("tiger.png");
        }
        else
        {
           // read_image("puzzle.png");
        }

        // We expect [c,h,w] order in deepracin but the loaded data has order [h,w,c], therefore we swap axes and cast to float
        for(j = 0; j < width*height*3; j++)
        {
 //           feed_buffer[j] = (float)(row_pointers[(j/width)%height][(j%width)*3+j/(width*height)]);
        	feed_buffer[j] = 1;
        }

        // Feed data to graph
        dR_feedData(net,feedlist[0],(cl_float*)feed_buffer,0,buffersize/sizeof(float));

        // Apply the graph
        dR_apply(net);

        // Download content from previously declared and fetched output buffer (Softmax output)
        dR_downloadArray(net,"", outbuffers[0],0,1000*sizeof(cl_float),odata);

        // Parse Classfile and print class
        float max = odata[0];
        int argmax = 0;
        gchar classfilename[] = "synset.txt";
        FILE *classfile = fopen(classfilename, "r");
        gint count = 0;
        for(j=0;j<1000;j++)
        {
            if(odata[j]>max)
            {
                max = odata[j];
                argmax = j;
            }
        }
        printf("5 \n");

        g_print("\n");
        if ( classfile != NULL )
        {
            gchar line[256];
            while (fgets(line, sizeof line, classfile) != NULL)
            {
                if (count == argmax)
                {
                    break;
                }
                else
                {
                    count++;
                }
            }
            fclose(classfile);
            g_print("Classification Result: Class %d, %s",argmax, line);
	    if(i%2==0)
            {
                g_print("Should be: Class 292, tiger, Panthera tigris.\n\n");
            }
            else
            {
                g_print("Should be: Class 611, jigsaw puzzle.\n\n");
            }
        }
        else
        {
            g_print("Failed to read class name file! \n\n");
        }

        // Show image
        g_print("Press Enter to continue...\n");
        getchar();
    }

    // Cleanup image read buffers
    for (y=0; y<height; y++)
//        free(row_pointers[y]);
//    free(row_pointers);
    free(feed_buffer);

    dR_cleanup(net, TRUE);
    printf("6 \n");
    return 0;

    /*

        printf("t1\n");

        gint feednode_it=0;
        dR_Node** graphnodes;
        dR_Node** feednodes;
        gint number_of_nodes;
        gint number_of_feednodes;
        printf("t2\n");

        number_of_nodes = 48;
        number_of_feednodes = 1;
        dR_Node*** outnodes;
        dR_Node*** outfeednodes;
        gint* numfeednodes;
        *outnodes = (dR_Node**) g_malloc(number_of_nodes*sizeof(dR_Node*));
        *outfeednodes = (dR_Node**) g_malloc(number_of_feednodes*sizeof(dR_Node*));
        printf("t3\n");

        graphnodes = *outnodes;
        feednodes = *outfeednodes;
        printf("t4\n");

        gchar* params[10];
        gfloat* variables[2];
        gchar* variableFilenames[2];
        gint num_variables;
        gint num_params;ERROR: offset+size > mem size

        gint id;
        gint it = 0;
        gint prev_nodes[256];
        gint num_prev_nodes;
        dR_Node** input;
        dR_Node* node;



        id = 0;
        printf("Node: %i\n", id);
        params[0] = 224;
        params[1] = 224;
        params[2] = 3;
        num_params = 3;
        num_prev_nodes = 0;
po        num_variables = 0;
        node = dR_datafeednlastnodeode_parseAppendNode(net,NULL,num_prev_nodes,params,num_params,variables,num_variables);
        graphnodes[id] = node;

        dR_printNetObject(net, NULL);

        id = 1;
        printf("Node: %i\n", id);
        params[0] = 0;
        params[1] = 0;
        params[2] = 0;
        params[3] = 0;
        params[4] = 224;
        params[5] = 224;
        params[6] = 1;
        params[7] = 0;
        num_params = 8;
        num_prev_nodes = 1;
        prev_nodes[0] = 0;
        input = malloc(num_prev_nodes*sizeof(dR_Node*));
        for(it=0;it<num_prev_nodes;it++)
        {
            input[it] = graphnodes[prev_nodes[it]];
        }
        num_variables = 0;
        node = dR_slice_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        free(input);
        graphnodes[id] = node;




         id = 2;
         printf("Node: %i\n", id);
         params[0] = 1;
         params[1] = '123.680000';
         num_params = 2;
         num_prev_nodes = 1;
         prev_nodes[0] = 1;
         input = malloc(num_prev_nodes*sizeof(dR_Node*));
         for(it=0;it<num_prev_nodes;it++)
         {
             input[it] = graphnodes[prev_nodes[it]];
         }
         num_variables = 0;
         node = dR_elemwise1op_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
         free(input);
         graphnodes[id] = node;




         id = 3;
         printf("Node: %i\n", id);
         params[0] = 0;
         params[1] = 0;
         params[2] = 1;
         params[3] = 0;
         params[4] = 224;
         params[5] = 224;
         params[6] = 1;
         params[7] = 0;
         num_params = 8;
         num_prev_nodes = 1;
         prev_nodes[0] = 0;
         input = malloc(num_prev_nodes*sizeof(dR_Node*));
         for(it=0;it<num_prev_nodes;it++)
         {
             input[it] = graphnodes[prev_nodes[it]];
         }
         num_variables = 0;
         node = dR_slice_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
         free(input);
         graphnodes[id] = node;




         id = 4;
         printf("Node: %i\n", id);
         params[0] = 1;
         params[1] = '116.778999';
         num_params = 2;
         num_prev_nodes = 1;
         prev_nodes[0] = 3;
         input = malloc(num_prev_nodes*sizeof(dR_Node*));
         for(it=0;it<num_prev_nodes;it++)
         {
             input[it] = graphnodes[prev_nodes[it]];
         }
         num_variables = 0;
         node = dR_elemwise1op_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
         free(input);
         graphnodes[id] = node;


        graphnodes[id] = node;
        for(it=0;it<num_variables;it++)
        {
            g_free(variables[it]);
        }
        if(num_prev_nodes>0)
        {
            g_free(input);
        }






        id = 5;
        printf("Node: %i\n", id);
        params[0] = 0;
        params[1] = 0;
        params[2] = 2;
        params[3] = 0;
        params[4] = 224;
        params[5] = 224;
        params[6] = 1;
        params[7] = 0;
        num_params = 8;
        num_prev_nodes = 1;
        prev_nodes[0] = 0;
        input = malloc(num_prev_nodes*sizeof(dR_Node*));
        for(it=0;it<num_prev_nodes;it++)
        {
            input[it] = graphnodes[prev_nodes[it]];
        }
        num_variables = 0;
        node = dR_slice_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        free(input);
        graphnodes[id] = node;





        id = 6;
        printf("Node: %i\n", id);
        params[0] = 1;
        params[1] = '103.939003';
        num_params = 2;
        num_prev_nodes = 1;
        prev_nodes[0] = 5;
        input = malloc(num_prev_nodes*sizeof(dR_Node*));
        for(it=0;it<num_prev_nodes;it++)
        {
            input[it] = graphnodes[prev_nodes[it]];
        }
        num_variables = 0;
        node = dR_elemwise1op_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        free(input);
        graphnodes[id] = node;






        id = 7;
        printf("Node: %i\n", id);
        params[0] = 3;
        params[1] = 2;
        num_params = 2;
        num_prev_nodes = 3;
        prev_nodes[0] = 6;
        prev_nodes[1] = 4;
        prev_nodes[2] = 2;
        input = malloc(num_prev_nodes*sizeof(dR_Node*));
        for(it=0;it<num_prev_nodes;it++)
        {
            input[it] = graphnodes[prev_nodes[it]];
        }
        num_variables = 0;
        node = dR_concat_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        free(input);
        graphnodes[id] = node;




        id = 8;
        printf("Node: %i\n", id);
        params[0] = 1;
        params[1] = 1;
        params[2] = 3;
        params[3] = 3;
        params[4] = 3;
        params[5] = 64;
        params[6] = 1;
        params[7] = 1;
        params[8] = 1;
        params[9] = 1;
        num_params = 10;
        num_prev_nodes = 1;
        prev_nodes[0] = 7;
        input = malloc(num_prev_nodes*sizeof(dR_Node*));
        for(it=0;it<num_prev_nodes;it++)
        {
            input[it] = graphnodes[prev_nodes[it]];
        }
        num_variables = 2;
        for(it=0;it<num_variables;it++)
        {
            gsize length;
            gchar* filecontentV;
            char filepath[] = "squeezenet_whole/";
            strcat(filepath, variableFilenames[it]);
            printf(filepath);
            g_file_get_contents(filepath,&filecontentV,&length, NULL);

            printf("\n var 0: ");
            variables[it] = (gfloat*)filecontentV;
            printf("%i \n", variables[0]);

            free(filecontentV);
        }
        for(int i2 = 0; i2<2;i2++){
        	printf("  %i : %s \n", i2, params[i2]);
            fflush(stdout);        //  Flush the stream.
        }
        node = dR_conv2d_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        free(input);
        graphnodes[id] = node;











       graphnodes[id] = node;
       for(it=0;it<num_variables;it++)
       {
           g_free(variables[it]);
       }
       if(num_prev_nodes>0)
       {
           g_free(input);
       }*/


/*
}

*/

/*
int main(){

	int inputs1[] = {1,1,0,0};
	int inputs2[] = {1,0,0,1};


	//int i,j;
	width = 2;
	height = 1;
    int buffersize = width*height*1*sizeof(float);
    float* feed_buffer = malloc(buffersize);


    // Required Pointers and Variables
    dR_Graph* net;
    dR_Node** feedlist;
    dR_Node** nodeslist;
    gint numnodes;
    gint numfeeds;
    dR_Node* lastnode;

    // New deepracin graph    printf("t1\n");

    net = dR_NewGraph();


    // Configure deepracin
    // Do not display debug information
     net->config->debugInfo = FALSE;
    // Profile GPU runtime
     net->config->profilingGPU = FALSE;
    // Profile CPU runtime
     net->config->profilingCPU = TRUE;
     // Give command line output
    net->config->silent = FALSE;
     // No Platform Hint - Choose first GPU available
    net->clConfig->clPlatformName = NULL;

    net->clConfig->clDeviceType = CL_DEVICE_TYPE_ACCELERATOR;

    // Initialize OpenCL
   dR_initCL(net);

    // Load dR Model and get list of nodes and data feed nodes
    dR_loadGraph(net,"squeezenet_whole/",&nodeslist,&numnodes,&feedlist,&numfeeds);
    lastnode = nodeslist[numnodes-1];

    // Mark the output nodes whose output buffers can be fetched with dR_getOutputBuffers
    // Nodes marked as output are guaranteed to have consistent output buffers after using dR_apply()
    dR_setAsOutput(net,lastnode);

    // Print network to console
    //dR_printNetObject(net, NULL);

    // Prepare network for execution - scheduling, buffer creation, kernel creation is done here
    dR_prepare(net);

    cl_float* odata = (gfloat*)g_malloc(1*sizeof(gfloat));
    cl_mem* outbuffers[1];

    // Fetch pointers to output buffers
    dR_getOutputBuffers(net,outbuffers);

    // initialize_image_buffer();
   g_print("Start applying graph...\n");
   size_t cl_mem_size;
   clGetMemObjectInfo(*outbuffers[0], CL_MEM_SIZE, sizeof(size_t), &cl_mem_size, NULL);
   printf("CL Memory Size: %zu , wanted: %zu\n", cl_mem_size, 1000*sizeof(cl_float));
    for(int i=0;i<4;i++) {
    	/*for(int j = 0; j < width*height*1; j++){
    		feed_buffer[j] = 1;
    	 }*//*
    	feed_buffer[0] = inputs1[i];
    	feed_buffer[1] = inputs2[i];
    	 // Feed data to graph
    	 dR_feedData(net,feedlist[0],(cl_float*)feed_buffer,0,buffersize/sizeof(float));
    	 // Apply the graph
    	 dR_apply(net);

    	 // Download content from previously declared and fetched output buffer (Softmax output)
    	 dR_downloadArray(net,"", outbuffers[0],0,1*sizeof(cl_float),odata);

    	 float max = odata[0];

    	 printf("Input1: %i Input2: %i Output: %i \n", inputs1[i], inputs2[i], odata[0]);
    }
/*
    	 int argmax = 0;
    	 for(int j=0;j<10;j++){
    		 if(odata[j]>max){
    			 max = odata[j];
    			 argmax = j;
    		 }
    	 }
    	    gchar * line = "0";
    	        g_print("\n");
    	        g_print("Classification Result: Class %d, %s",argmax, line);
    	 	    if(i%2==0){
    	                 g_print("Should be: Class 292, tiger, Panthera tigris.\n\n");
    	        }else{
    	                 g_print("Should be: Class 611, jigsaw puzzle.\n\n");
    	        }


		}*//*


    free(feed_buffer);

    dR_cleanup(net, TRUE);
	return 0;
}*/



int main(){

	float inputs1[] = {1,1,0,0,1,0,1,0};
	float inputs2[] = {1,0,0,1,1,0,0,1};


	//int i,j;
	width = 2;
	height = 1;
    int buffersize = width*height*1*sizeof(float);
    float* feed_buffer = (float *) malloc(buffersize);

    // Required Pointers and Variables
    dR_Graph* net;
    dR_Node** feedlist;
    dR_Node** nodeslist;
    gint numnodes;
    gint numfeeds;
    dR_Node* lastnode;

    // New deepracin graph    printf("t1\n");
    double time1=0.0, tstart;
    tstart = clock();
    net = dR_NewGraph();


    // Configure deepracin
    // Do not display debug information
     net->config->debugInfo = FALSE;
    // Profile GPU runtime
     net->config->profilingGPU = FALSE;
    // Profile CPU runtime
     net->config->profilingCPU = TRUE;
     // Give command line output
    net->config->silent = FALSE;
     // No Platform Hint - Choose first GPU available
    net->clConfig->clPlatformName = NULL;

    net->clConfig->clDeviceType = CL_DEVICE_TYPE_ACCELERATOR;

    // Initialize OpenCL
   dR_initCL(net);

    // Load dR Model and get list of nodes and data feed nodes
    dR_loadGraph(net,"deepRacinModels/",&nodeslist,&numnodes,&feedlist,&numfeeds);
    lastnode = nodeslist[numnodes-1];

    // Mark the output nodes whose output buffers can be fetched with dR_getOutputBuffers
    // Nodes marked as output are guaranteed to have consistent output buffers after using dR_apply()
    dR_setAsOutput(net,lastnode);

    // Print network to console
    //dR_printNetObject(net, NULL);

    // Prepare network for execution - scheduling, buffer creation, kernel creation is done here
    dR_prepare(net);

    cl_float* odata = (gfloat*)g_malloc(1000*sizeof(gfloat));
    cl_mem* outbuffers[1];

    // Fetch pointers to output buffers
    dR_getOutputBuffers(net,outbuffers);

    // initialize_image_buffer();
   g_print("Start applying graph...\n");
   size_t cl_mem_size;
   clGetMemObjectInfo(*outbuffers[0], CL_MEM_SIZE, sizeof(size_t), &cl_mem_size, NULL);
   //printf("CL Memory Size: %zu , wanted: %zu\n", cl_mem_size, 1000*sizeof(cl_float));
    for(int i=0;i<8;i++) {
    	/*for(int j = 0; j < width*height*1; j++){
    		feed_buffer[j] = 1;
    	 }*/
    	feed_buffer[0] = inputs1[i];
    	feed_buffer[1] = inputs2[i];
    	 // Feed data to graph
    	 dR_feedData(net,feedlist[0],(cl_float*)feed_buffer,0,buffersize/sizeof(float));
    	 // Apply the graph
    	 dR_apply(net);

    	 // Download content from previously declared and fetched output buffer (Softmax output)
    	 dR_downloadArray(net,"", outbuffers[0],0,1*sizeof(cl_float),odata);

    	 printf("Input1: %f Input2: %f Output: %f \n", feed_buffer[0], feed_buffer[1], odata[0]);
    }
    time1 += clock() - tstart;
    time1 = time1/CLOCKS_PER_SEC;
    printf("  time = %f",time1);//
/*
    	 int argmax = 0;
    	 for(int j=0;j<10;j++){
    		 if(odata[j]>max){
    			 max = odata[j];
    			 argmax = j;
    		 }
    	 }
    	    gchar * line = "0";
    	        g_print("\n");
    	        g_print("Classification Result: Class %d, %s",argmax, line);
    	 	    if(i%2==0){
    	                 g_print("Should be: Class 292, tiger, Panthera tigris.\n\n");
    	        }else{
    	                 g_print("Should be: Class 611, jigsaw puzzle.\n\n");
    	        }


		}*/


    free(feed_buffer);

    dR_cleanup(net, TRUE);
	return 0;
}

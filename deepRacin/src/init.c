#include"deepRACIN.h"


/*
dR_Node* dR_loadGraphC(dR_Graph* net, gchar* path, dR_Node*** outnodes, gint* numnodes, dR_Node*** outfeednodes, gint* numfeednodes)
{
    gsize length;
    gchar* filecontent;
    gchar* filepath;
    gint i;
    gint feednode_it=0;
    dR_Node** graphnodes;
    dR_Node** feednodes;
    gboolean success;
    gchar* lineptr;
    gchar* inlineptr;
    gchar* line;
    gchar* token;

    gint number_of_nodes;
    gint number_of_feednodes;
    GError *err = NULL;

    if(net->number_of_layers!=0)
    {
         g_print("dR_parseGraph can only fill an empty graph! Given graph not empty!\n");
         return 0;
    }
    /*net->config->modelPath = g_strdup(path);

    filepath = g_build_filename(path, "graph.dr", NULL);

    if(!net->config->silent)
        g_print("Loading Model File %s ...\n",path);

    success = g_file_get_contents(filepath,&filecontent,&length,&err);

    if(!success)
    {
        g_print("Error while opening the graph file.\n");
        return 0;
    }

    line = own_strtok_r(filecontent,"\n",&lineptr);
	*/

    // Get number of nodes and feed nodes;
    //own_strtok_r(line," ",&inlineptr);
    //own_strtok_r(NULL," ",&inlineptr);
/*   number_of_nodes = 4; //atoi(own_strtok_r(NULL," ",&inlineptr));
    //own_strtok_r(NULL," ",&inlineptr);
    number_of_feednodes = 4;

    *outnodes = g_malloc(number_of_nodes*sizeof(dR_Node*));
    *outfeednodes = g_malloc(number_of_feednodes*sizeof(dR_Node*));
    *numnodes = number_of_nodes;
    *numfeednodes = number_of_feednodes;
    graphnodes = *outnodes;
    feednodes = *outfeednodes;

    if(!net->config->silent)
        g_print("Found graph with %d nodes and %d feed nodes.\n",number_of_nodes,number_of_feednodes);

    // Build graph
    for(i=0;i<number_of_nodes;i++)
    {
        gchar* desc;
        // Currently no node type has more than 10 parameters and 2 variables
        gchar* params[10];
        gfloat* variables[2];
        gchar* variableFilenames[2];
        gint num_variables;
        gint num_params;
        gint id;
        gint it = 0;
        // Hard cap 256 of previous nodes...
        gint prev_nodes[256];
        gint num_prev_nodes;
        dR_Node** input;
        dR_Node* node;

        //line = own_strtok_r(NULL,"\r\n",&lineptr);

        //own_strtok_r(line, " ",&inlineptr);
       // id = atoi(own_strtok_r(NULL, " ",&inlineptr));
        //desc = own_strtok_r(NULL, " ",&inlineptr);

        if(!net->config->silent&&net->config->debugInfo)
            g_print("Loading Node %d\n",id);

        // Get params
        //line = own_strtok_r(NULL,"\r\n",&lineptr);

       // token = own_strtok_r(line, " ",&inlineptr);
        token = own_strtok_r(NULL, " ",&inlineptr);
        while(token != NULL) {
            params[it] = token;
            token = own_strtok_r(NULL, " ",&inlineptr);
            it++;
        }
        num_params = it;

        // Get prev_nodes
        line = own_strtok_r(NULL,"\r\n",&lineptr);

        token = own_strtok_r(line, " ",&inlineptr);
        token = own_strtok_r(NULL, " ",&inlineptr);
        it = 0;
        while(token != NULL) {
            prev_nodes[it] = atoi(token);
            token = own_strtok_r(NULL, " ",&inlineptr);
            it++;
        }
        num_prev_nodes = it;

        // Ignore next_node line
        line = own_strtok_r(NULL,"\r\n",&lineptr);

        // Get variables
        line = own_strtok_r(NULL,"\r\n",&lineptr);

        token = own_strtok_r(line, " ",&inlineptr);
        token = own_strtok_r(NULL, " ",&inlineptr);
        it = 0;
        while(token != NULL) {
            variableFilenames[it] = token;
            token = own_strtok_r(NULL, " ",&inlineptr);
            it++;
        }
        num_variables = it;

        if(!net->config->silent&&net->config->debugInfo)
            g_print("Found %s with id %d, %d params and %d variables\n",desc,id,num_params,num_variables);
        // Load variables
        for(it=0;it<num_variables;it++)
        {
            gsize length;
            gchar* filecontent;
            gchar* filepath;
            filepath = g_build_filename(path,variableFilenames[it], NULL);
            success = g_file_get_contents(filepath,&filecontent,&length,&err);
            variables[it] = (gfloat*)filecontent;
            if(!success)
            {
                g_print("Error while opening variable file: %s, Length: %d, Errcode: %d\n", filepath, length, *err);
                return 0;
            }
            g_free(filepath);
        }

        if(num_prev_nodes>0)
        {
            input = g_malloc(num_prev_nodes*sizeof(dR_Node*));
            for(it=0;it<num_prev_nodes;it++)
            {
                input[it] = graphnodes[prev_nodes[it]];
            }
        }

        if(strncmp(desc, "Conv2D", strlen("Conv2D"))==0)
        {
            if(num_prev_nodes!=1)
            {
                g_print("Failed to parse Conv2d node!\n");
                return 0;
            }
            node = dR_conv2d_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        }
        else if(strncmp(desc, "Conv2DTranspose", strlen("Conv2DTranspose"))==0)
        {
            if(num_prev_nodes!=1)
            {
                g_print("Failed to parse Conv2DTranspose node!\n");
                return 0;
            }
            node = dR_conv2dtranspose_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        }
        else if(strncmp(desc, "Pooling", strlen("Pooling"))==0)
        {
            if(num_prev_nodes!=1)
            {
                g_print("Failed to parse Pooling node!\n");
                return 0;
            }
            node = dR_pooling_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        }
        else if(strncmp(desc, "FullyConnected", strlen("FullyConnected"))==0)
        {
            if(num_prev_nodes!=1)
            {
                g_print("Failed to parse FullyConnected node!\n");
                return 0;
            }
            node = dR_fc_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        }
        else if(strncmp(desc, "PPFilter", strlen("PPFilter"))==0)
        {
            if(num_prev_nodes!=2)
            {
                g_print("Failed to parse PPFilter node!\n");
                return 0;
            }
            node = dR_conv2duw_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        }
        else if(strncmp(desc, "MaskDependentFilter", strlen("MaskDependentFilter"))==0)
        {
            if(num_prev_nodes!=2)
            {
                g_print("Failed to parse MaskDependentFilter node!\n");
                return 0;
            }
            node = dR_cdfilter_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        }
        else if(strncmp(desc, "LabelCreation", strlen("LabelCreation"))==0)
        {
            if(num_prev_nodes!=1)
            {
                g_print("Failed to parse LabelCreation node!\n");
                return 0;
            }
            node = dR_lc_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        }
        else if(strncmp(desc, "Normalization", strlen("Normalization"))==0)
        {
            if(num_prev_nodes!=1)
            {
                g_print("Failed to parse Normalization node!\n");
                return 0;
            }
            node = dR_norm_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        }
        else if(strncmp(desc, "Upscaling", strlen("Upscaling"))==0)
        {
            if(num_prev_nodes!=1)
            {
                g_print("Failed to parse Upscaling node!\n");
                return 0;
            }
            node = dR_us_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        }
        else if(strncmp(desc, "RGB2Gray", strlen("RGB2Gray"))==0)
        {
            if(num_prev_nodes!=1)
            {
                g_print("Failed to parse RGB2Gray node!\n");
                return 0;
            }
            node = dR_rgb2gray_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        }
        else if(strncmp(desc, "ResolveRoI", strlen("ResolveRoI"))==0)
        {
            if(num_prev_nodes!=1)
            {
                g_print("Failed to parse ResolveRoI node!\n");
                return 0;
            }
            node = dR_resolveRoI_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        }
        else if(strncmp(desc, "Softmax", strlen("Softmax"))==0)
        {
            if(num_prev_nodes!=1)
            {
                g_print("Failed to parse Softmax node!\n");
                return 0;
            }
            node = dR_softmax_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        }
        else if(strncmp(desc, "Slice", strlen("Slice"))==0)
        {
            if(num_prev_nodes!=1)
            {
                g_print("Failed to parse Slice node!\n");
                return 0;
            }
            node = dR_slice_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        }
        else if(strncmp(desc, "Concat", strlen("Concat"))==0)
        {
            if(num_prev_nodes<=1)
            {
                g_print("Failed to parse Concat node!\n");
                return 0;
            }
            node = dR_concat_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        }
        else if(strncmp(desc, "CropOrPad", strlen("CropOrPad"))==0)
        {
            if(num_prev_nodes!=1)
            {
                g_print("Failed to parse Conv2d node!\n");
                return 0;
            }
            node = dR_croporpad_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        }
        else if(strncmp(desc, "ElemWise2Op", strlen("ElemWise2Op"))==0)
        {
            if(num_prev_nodes!=2)
            {
                g_print("Failed to parse ElemWise2Op node!\n");
                return 0;
            }
            node = dR_elemwise2op_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        }
        else if(strncmp(desc, "ElemWise1Op", strlen("ElemWise1Op"))==0)
        {
            if(num_prev_nodes!=1)
            {
                g_print("Failed to parse Conv2d node!\n");
                return 0;
            }
            node = dR_elemwise1op_parseAppendNode(net,input,num_prev_nodes,params,num_params,variables,num_variables);
        }
        else if(strncmp(desc, "DataFeedNode", strlen("DataFeedNode"))==0)
        {
            if(num_prev_nodes!=0)
            {
                g_print("Failed to parse DataFeedNode node!\n");
                return 0;
            }
            node = dR_datafeednode_parseAppendNode(net,NULL,num_prev_nodes,params,num_params,variables,num_variables);
            feednodes[feednode_it] = node;
            feednode_it++;
        }
        else
        {
            g_print("Parsing Error: Node could not be identified: %s!\n", desc);
            return NULL;
        }
        if(node==NULL)
        {
            g_print("Parsing Error: Node could not be appended!\n");
            return NULL;
        }
        graphnodes[id] = node;
        for(it=0;it<num_variables;it++)
        {
            g_free(variables[it]);
        }
        if(num_prev_nodes>0)
        {
            g_free(input);
        }
    }
    g_free(filecontent);
    g_free(filepath);
    return graphnodes[number_of_nodes-1];
}*/



int sqnet(){
	//Leeren GRaph erstellen
	dR_Graph* net = dR_NewGraph();
	*net->prepared = false;
	dR_config(net, "Xilinx", false, true, false, false, "/");

	dR_ClConfig clConfig;
	cl_context* context;
	dR_createClContext(context, 1, (cl_device_id*)1);
	clConfig.clContext = *context;


	// Load Graph
	net = dR_NewGraph();
	dR_loadGraphC(net,model_path,&nodeslist,&numnodes,&feedlist,&numfeeds);

	// Mark Output Node
	dR_setAsOutput(net,nodeslist[numnodes-1]);

	// Initialize OpenCL
	dR_initCL(net);

	// Setup and schedule everything
	dR_prepare(net);

	// Get OpenCL buffers for outputs
	dR_getOutputBuffers(net,outbuffers);

	for(int i = 0; i<numImages;i++)
	{
	    // Feed data
	    dR_feedData(net,feedlist[0],(cl_float*)data[i],0,buffersize*sizeof(cl_float));
	    // Apply graph
	    dR_apply(net);
	    // Get output data
	    dR_downloadArray(net,"", outbuffers[0],0,out_size*sizeof(cl_float),data_out);
	}
	return 0;
}

int xor(){
	Graph* net = dR_NewGraph();

}

int main(){
	Graph graph;


	dR_prepare(*graph);

	return 0;
}

void dR_config(dR_Graph* net,
                                gchar* platformname,
                                gboolean silent,
                                gboolean debuginfo,
                                gboolean profileGPU,
                                gboolean profileCPU,
                                gchar* temppath);


#include "dR_offline_kernel.h"
#include "dR_core.h"
#include <stdio.h>


gboolean dR_clOfflineBuildWithSource(dR_Graph* net, const gchar * const filenames[], gint numberoffiles)
{
    gchar * sourceCodes[25] = { NULL };
    size_t sourceCodeLengths[25] = { 0 };
    cl_uint numberOfCodes = numberoffiles;
    cl_uint numberOfFiles = numberoffiles;
    gboolean kernelLoadSuccess;
    guint i;
    gchar * filePath = NULL;
    GError *err = NULL;
    gsize length;
#ifndef GPGPU_SIM_MODE
    size_t len;
#endif
    gint totalLength = 0;
    gboolean error = FALSE;
#ifdef GPGPU_SIM_MODE
    gchar * gpgpuSimCode;
    gsize destPos;
#endif

    dR_Node* current_layer;
	int numGeneratedCodes;
	gchar** genKernelFilenames;
    int sourceindex= 0;
    gboolean loadedKernel = FALSE;

    if (!net->config->silent)
        g_print("Loading kernels...\n");

    if (!net->config->silent&&net->config->debugInfo)
        g_print("from %s...\n", net->clConfig->clKernelPath);

    dR_list_resetIt(net->scheduledLayers);
    current_layer = (dR_Node*)dR_list_next(net->scheduledLayers);
    while(current_layer){
        if(current_layer->createKernelName)
            numberOfCodes++;
        current_layer = (dR_Node*)dR_list_next(net->scheduledLayers);
    }
    printf("offlineKernel 1 \n");
    if (!net->config->silent&&net->config->debugInfo)
        g_print("Number of Kernelfiles: %d \n", numberOfCodes);
    numGeneratedCodes = numberOfCodes-numberOfFiles;
    genKernelFilenames = g_malloc(sizeof(gchar*)*numGeneratedCodes);
    dR_list_resetIt(net->scheduledLayers);
    current_layer = (dR_Node*)dR_list_next(net->scheduledLayers);
    //loading kernels form file
    //numberOfCodes=26;
   /* for(i=0; i < numberOfCodes; ++i)
    {
    	printf("numberofcodes: %i\n", i);
        loadedKernel = FALSE;
        if (i == 0 && net->clConfig->configH != NULL && net->clConfig->configH[0] != '\0')
        {
            //Use config.h from given path
            if (!net->config->silent)
            {
                g_print("Loading manually set config.h from %s...\n", net->clConfig->configH);
            }
            kernelLoadSuccess = g_file_get_contents(net->clConfig->configH, &(sourceCodes[sourceindex]), &length, &err);
//            kernelLoadSuccess = g_file_get_contents(net->clConfig->configH, (sourceCodes[sourceindex]), &length, &err);
            loadedKernel = TRUE;
            sourceindex++;
        }
        else
        {
            if(i<numberOfFiles)
            {
                //Load kernel file i

                filePath = filenames[i];
            	//filePath = "binary_container_1.xclbin";
            	printf("filePath: %s\n", filePath);

                //filePath = g_build_filename(net->clConfig->clKernelPath, filenames[i], NULL);
                if (!net->config->silent&&net->config->debugInfo)
                {
                    g_print("Loading kernel file %s...\n", filePath);
                }
//                kernelLoadSuccess = g_file_get_contents(filePath, (sourceCodes[sourceindex]), &length, &err);
                kernelLoadSuccess = g_file_get_contents(filePath, &(sourceCodes[sourceindex]), &length, &err);
                g_free((gpointer)filePath);
                loadedKernel = TRUE;
                sourceindex++;
            }
            else
            {
                while(current_layer&&!current_layer->createKernelName)
                {
                    current_layer = (dR_Node*)dR_list_next(net->scheduledLayers);
                }
                if(current_layer&&current_layer->createKernelName)
                {
                    genKernelFilenames[sourceindex-numberOfFiles] = current_layer->createKernelName(current_layer);
                    filePath = g_build_filename(net->config->modelPath, genKernelFilenames[sourceindex-numberOfFiles], NULL);
                    if (!net->config->silent&&net->config->debugInfo)
                    {
                        g_print("Loading kernel file %s...\n", filePath);
                    }
//                    kernelLoadSuccess = g_file_get_contents(filePath, (sourceCodes[sourceindex]), &length, &err);
                    kernelLoadSuccess = g_file_get_contents(filePath, &(sourceCodes[sourceindex]), &length, &err);
                    g_free((gpointer)filePath);
                    loadedKernel = TRUE;
                    if (!net->config->silent&&net->config->debugInfo)
                        g_print("Filename: %s\n", genKernelFilenames[sourceindex-numberOfFiles]);
                    sourceindex++;
                }
                current_layer = (dR_Node*)dR_list_next(net->scheduledLayers);
                //if (!net->config->silent&&net->config->debugInfo)
                //    g_print("Got generated kernel string with length: %d \n",(gint)length);
            }
        }
        if(loadedKernel)
        {
            if (!kernelLoadSuccess)
            {
                dR_openCLError(net, err->message, "clBuildWithSource");
                g_error_free(err);
                for(i=0; i < numberOfFiles; ++i)
                    if ( sourceCodes[i] ) g_free((gpointer)sourceCodes[i]);
                    else break;
                    return FALSE;
            }
            sourceCodeLengths[sourceindex-1] = length;
            totalLength += length;
            if (!net->config->silent&&net->config->debugInfo)
                g_print("Got generated kernel string with length: %d, total length: %d \n",(gint)length, (gint)totalLength);
        }
    }
    numberOfCodes = sourceindex;


    if (net->config->debugInfo)
    {
        g_print("\n");
        for(i=0; i < numberOfCodes; ++i)
        {
            if(i<numberOfFiles)
                g_print("Kernel file %i:\n%s\n", i, filenames[i]);
            else
                g_print("Kernel file %i:\n%s\n", i, genKernelFilenames[i-numberOfFiles]);
        }
    }

    if (!net->config->silent)
    {
        g_print("Done.\n");
        g_print("Creating OpenCL program... \n");
        g_print("Source code length: %d \n",(gint)totalLength);
    }*/

    //added
    printf("offlineKernel 2 \n");
    filePath = filenames[0];
	FILE *file;
	unsigned char *binaryString;
	file = fopen(filePath, "rb");
	if(!file){
		printf("Error: Kernel binary not found\n");
		return false;
	}
    printf("offlineKernel 3 \n");

	fseek(file, 0L, SEEK_END);
	size_t binaryFileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
	binaryString = (unsigned char *) malloc(binaryFileSize);
	size_t binarySize = fread(binaryString, 1, binaryFileSize, file);
	fclose(file);
    // create program
    net->clConfig->clProgram = clCreateProgramWithBinary(net->clConfig->clContext,
    	net->clConfig->clNumDevices,
		net->clConfig->clDeviceIds,
		&binaryFileSize,
		(const unsigned char **)&binaryString,
		NULL,
		&net->clConfig->clError);
    ///added

    if (!net->config->silent)
        g_print("Done.\n");

    if (!net->config->silent)
        g_print("Cleanup loaded kernels...\n");
    g_free(genKernelFilenames);
    for(i=0; i < numberOfCodes; ++i)
    {
        if (sourceCodes[i])
        {
            g_free((gpointer)sourceCodes[i]);
        }
        else
        {
            break;
        }
    }

    if (dR_openCLError(net, "Could not create OpenCL program!", "clInit"))
    {
        return FALSE;
    }

    if (!net->config->silent)
        g_print("Done.\n");

    if (!net->config->silent)
        g_print("Building OpenCL program... ");


    //compile program
        //Non-NVIDIA platform

            //Non-CPU
            if (net->clConfig->fastRelaxedMath)
            {
#ifdef _DEBUG
                if (!net->config->silent&&net->config->debugInfo)
                    g_print("clBuildProgram: Non-CPU in debug mode with fast-relaxed-math\n");
                net->clConfig->clError = clBuildProgram(net->clConfig->clProgram, 0, NULL, "-cl-opt-disable -w -cl-mad-enable -cl-fast-relaxed-math", NULL, NULL);
#else
                if (!net->config->silent&&net->config->debugInfo)
                    g_print("clBuildProgram: Non-CPU in release mode with fast-relaxed-math\n");
                net->clConfig->clError = clBuildProgram(net->clConfig->clProgram, 0, NULL, "-cl-mad-enable -cl-fast-relaxed-math", NULL, NULL);
#endif
            }
            else
            {
#ifdef _DEBUG
                if (!net->config->silent&&net->config->debugInfo)
                    g_print("clBuildProgram: Non-CPU in debug mode without fast-relaxed-math\n");
                net->clConfig->clError = clBuildProgram(net->clConfig->clProgram, 0, NULL, "-cl-opt-disable -w -cl-mad-enable", NULL, NULL);
#else
                if (!net->config->silent&&net->config->debugInfo)
                    g_print("clBuildProgram: Non-CPU in release mode without fast-relaxed-math\n");
                net->clConfig->clError = clBuildProgram(net->clConfig->clProgram, 0, NULL, "-cl-mad-enable", NULL, NULL);
#endif
            }


    error = dR_openCLError(net, "Could not build OpenCL program!", "clBuildWithSource");

    if (error == FALSE)
    {
        if (!net->config->silent)
            g_print("Done.\n");
    }
    else
    {
        g_print("Error while compiling the OpenCL program (%i).\n", error);
    }

    if (error == TRUE || net->config->debugInfo == TRUE)
    {
        //compile not successfully or just as debug info
#ifndef GPGPU_SIM_MODE
        net->clConfig->clError = clGetProgramBuildInfo(net->clConfig->clProgram, net->clConfig->clDeviceId, CL_PROGRAM_BUILD_STATUS, sizeof(cl_build_status), &net->clConfig->build_status, NULL);
        if (! dR_openCLErrorWithoutCleanup(net,"Could not get the OpenCL build status.", "clBuildWithSource"))
        {
            if (net->clConfig->build_status != CL_BUILD_SUCCESS || net->config->debugInfo == TRUE)
            {
                net->clConfig->clError = clGetProgramBuildInfo(net->clConfig->clProgram, net->clConfig->clDeviceId, CL_PROGRAM_BUILD_LOG, 0, NULL, &len);

                if (! dR_openCLErrorWithoutCleanup(net,"Could not get the OpenCL build log size.\n", "clBuildWithSource"))
                {
                    gchar * build_log_buffer = g_malloc(len+1);
                    net->clConfig->clError = clGetProgramBuildInfo(net->clConfig->clProgram, net->clConfig->clDeviceId, CL_PROGRAM_BUILD_LOG, len, build_log_buffer, NULL);
                    if (! dR_openCLErrorWithoutCleanup(net,"Could not get the OpenCL build log.\n", "clBuildWithSource"))
                    {
                        // to be carefully, terminate with \0
                        build_log_buffer[len] = '\0';
                        g_print("Build log: %s\n", build_log_buffer);
                        //GST_ELEMENT_WARNING(GST_ELEMENT(filter), STREAM, FAILED, ("Build log:\n%s", build_log_buffer), (NULL));
                    }
                    g_free((gpointer)build_log_buffer);
                }
            }
        }
#endif
        if (error == TRUE)
        {
            dR_cleanupCL(net);
            return FALSE;
        }
    } //compile successfully
    return TRUE;
}



//Creates Context for Xilinx OpenCL Platform
//return created context, nummber of Xilinx OpenCL devices and the list of device ids
bool dR_createOfflineClContext(cl_context* context, cl_uint* num_devices, cl_device_id* devices){

	int status;
	cl_uint num_platforms;
	cl_platform_id* platform_ids;

	//get all platform ids
	status = clGetPlatformIDs(0, NULL, &num_platforms);
	platform_ids = (cl_platform_id*) malloc(sizeof(cl_platform_id) * num_platforms);
	status = clGetPlatformIDs(num_platforms, platform_ids, NULL);
	if(status == CL_SUCCESS){
		g_print("Platform ID identified\n");
	} else if(status == CL_INVALID_VALUE){
		g_print("Invalid number of platforms");
		return false;
	}

	//get Xilinx platform
	int use_platform = -1;
	size_t param_value_size;
	char* param_value;
	for(int i = 0; i<num_platforms; i++){
		clGetPlatformInfo(platform_ids[i], CL_PLATFORM_NAME, NULL, NULL, &param_value_size);
		param_value = (char*)malloc(sizeof(char) * param_value_size);
		clGetPlatformInfo(platform_ids[i], CL_PLATFORM_NAME, param_value_size, param_value, NULL);
		if(strcmp(param_value, "Xilinx")){
			use_platform = i;
			break;
		}
	}
	if(use_platform == -1){
		g_print("No Xilinx OpenCL Platform detected! \n");
		return false;
	}

	//get device ids
	status = clGetDeviceIDs(platform_ids[use_platform],  CL_DEVICE_TYPE_ACCELERATOR,0, NULL, num_devices);
	devices = (cl_device_id*) malloc(sizeof(cl_device_id) * (*num_devices));
	status = clGetDeviceIDs(platform_ids[use_platform],  CL_DEVICE_TYPE_ACCELERATOR,num_devices, devices, NULL);
	//Error handling_
	if(status == CL_SUCCESS){
		g_print("Device ID identified\n");
	} else if(status == CL_INVALID_PLATFORM){
		g_print("Invalid platform found");
		return false;
	} else if(status == CL_INVALID_DEVICE_TYPE){
		g_print("Invalid device type requested");
		return false;
	} else if(status == CL_DEVICE_NOT_FOUND){
		g_print("OpenCL Device not found");
		return false;
	}

	//create context
	*context = clCreateContext(NULL, num_devices, devices, NULL, NULL, &status);
	//Error handling_
	if(status == CL_SUCCESS){
		g_print("OpenCL context created\n");
	} else if(status == CL_INVALID_PLATFORM){
		g_print("Invalid platform found");
		return false;
	} else if(status == CL_INVALID_VALUE){
		g_print("Unsupported arguments for clCreateContext");
		return false;
	} else if(status == CL_INVALID_DEVICE){
		g_print("Invalid device type for context");
		return false;
	} else if(status == CL_DEVICE_NOT_AVAILABLE) {
		g_print("OpenCL Device currently not available");
		return false;
	} else if(status == CL_OUT_OF_HOST_MEMORY) {
		g_print("allocate resources to the host memory failed");
		return false;
	}

	return true;
}


//Creates Program for Xilinx FPGA
//Parameter: program to be returned, priviously created context, number of OpenCL devices, device ids, OpenCL Kernel binaryPath, device name (E.g.: "zed" for Xilinx ZedBoard)
bool dR_createCLProgramFromBinary(cl_program* program, cl_context* context, cl_uint num_devices, cl_device_id* devices, char* path, char* device_name){

	int status;

	//read binarystream from file
	FILE *file;
	unsigned char *binaryString;
	file = fopen(path, "rb");
	if(!file){
		printf("Kernel binary not found");
		return false;
	}

	fseek(file, 0L, SEEK_END);
	size_t binaryFileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
	unsigned char *buffer;
	buffer = (unsigned char *)malloc(binaryFileSize);
	binaryString = (unsigned char *) malloc(binaryFileSize);
	size_t binarySize = fread(binaryString, 1, binaryFileSize, file);
	fclose(file);


	//create program from binarystream
	*program = clCreateProgramWithBinary(*context, num_devices, devices, &binaryFileSize, (const unsigned char **)&binaryString, NULL, &status);
	//Error handling:
	if(status == CL_SUCCESS) {
		printf("created OpenCL program from binary successfully\n");
	} else if(status == CL_INVALID_CONTEXT) {
		printf("invalid OpenCL context committed");
		return false;
	} else if(status == CL_INVALID_VALUE) {
		printf("Invalid device or length parameters");
		return false;
	} else if(status == CL_INVALID_BINARY) {
		printf("invalid binary parameter");
		return false;
	} else if(status == CL_OUT_OF_HOST_MEMORY) {
		printf("allocate resources to the host memory failed");
		return false;
	}


	//get Xilinx FPGA as device (E.g.: zed)
	int use_device = -1;
	size_t param_value_size;
	char* param_value;
	for(int i = 0; i<num_devices; i++){
		clGetDeviceInfo(devices[i], CL_DEVICE_NAME, NULL, NULL, &param_value_size);
		param_value = (char*)malloc(sizeof(char) * param_value_size);
		clGetDeviceInfo(devices[i], CL_DEVICE_NAME, param_value_size, param_value, NULL);
		if(strcmp(param_value, device_name)){
			use_device = i;
			break;
		}
	}
	if(use_device == -1){
		g_print("%s not detected! \n", device_name);
		return false;
	}

	//build program
	status = clBuildProgram(*program, 1, devices, NULL, NULL, NULL);
	if(status == CL_SUCCESS) {
		printf("OpenCL program successfully build\n");
	} else if(status == CL_INVALID_PROGRAM) {
		printf("invalid OpenCL program committed");
		return false;
	} else if(status == CL_INVALID_VALUE) {
		printf("device_list is NULL and num_devices is greater than zero, or if device_list is not NULL and num_devices is zero");
		return false;
	} else if(status == CL_INVALID_DEVICE) {
		printf("OpenCL devices listed in device_list are not in the list of devices associated with program");
		return false;
	} else if(status == CL_OUT_OF_HOST_MEMORY) {
		printf("allocate resources to the host memory failed");
		return false;
	}else if(status == CL_INVALID_BINARY) {
		printf("program is created with clCreateWithProgramWithBinary and devices listed in device_list do not have a valid program binary loaded. ");
		return false;
	} else if(status == CL_COMPILER_NOT_AVAILABLE) {
		printf("program is created with clCreateProgramWithSource and a compiler is not available");
		return false;
	} else if(status == CL_BUILD_PROGRAM_FAILURE) {
		printf("there is a failure to build the program executable");
		return false;
	}

	return true;
}

/*
dR_ClConfig new_offline_clConfig(){
	dR_ClConfig clConfig;
	clContext context;
	dR_createClContext(&context, 1, cl_device_id*(1));
	clConfig.clContext = context;

	return clConfig;
}*/

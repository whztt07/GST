#ifndef __GENTC_CL_GUARDS_H__
#define __GENTC_CL_GUARDS_H__

#ifndef NDEBUG
static inline const char *clErrMsg(cl_int err) {
  const char *errMsg = NULL;
  switch(err) {
  case CL_SUCCESS:                         errMsg = "Success!"; break;
  case CL_DEVICE_NOT_FOUND:                errMsg = "Device not found."; break;
  case CL_DEVICE_NOT_AVAILABLE:            errMsg = "Device not available"; break;
  case CL_COMPILER_NOT_AVAILABLE:          errMsg = "Compiler not available"; break;
  case CL_MEM_OBJECT_ALLOCATION_FAILURE:   errMsg = "Memory object allocation failure"; break;
  case CL_OUT_OF_RESOURCES:                errMsg = "Out of resources"; break;
  case CL_OUT_OF_HOST_MEMORY:              errMsg = "Out of host memory"; break;
  case CL_PROFILING_INFO_NOT_AVAILABLE:    errMsg = "Profiling information not available"; break;
  case CL_MEM_COPY_OVERLAP:                errMsg = "Memory copy overlap"; break;
  case CL_IMAGE_FORMAT_MISMATCH:           errMsg = "Image format mismatch"; break;
  case CL_IMAGE_FORMAT_NOT_SUPPORTED:      errMsg = "Image format not supported"; break;
  case CL_BUILD_PROGRAM_FAILURE:           errMsg = "Program build failure"; break;
  case CL_MAP_FAILURE:                     errMsg = "Map failure"; break;
  case CL_INVALID_VALUE:                   errMsg = "Invalid value"; break;
  case CL_INVALID_DEVICE_TYPE:             errMsg = "Invalid device type"; break;
  case CL_INVALID_PLATFORM:                errMsg = "Invalid platform"; break;
  case CL_INVALID_DEVICE:                  errMsg = "Invalid device"; break;
  case CL_INVALID_CONTEXT:                 errMsg = "Invalid context"; break;
  case CL_INVALID_QUEUE_PROPERTIES:        errMsg = "Invalid queue properties"; break;
  case CL_INVALID_COMMAND_QUEUE:           errMsg = "Invalid command queue"; break;
  case CL_INVALID_HOST_PTR:                errMsg = "Invalid host pointer"; break;
  case CL_INVALID_MEM_OBJECT:              errMsg = "Invalid memory object"; break;
  case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR: errMsg = "Invalid image format descriptor"; break;
  case CL_INVALID_IMAGE_SIZE:              errMsg = "Invalid image size"; break;
  case CL_INVALID_SAMPLER:                 errMsg = "Invalid sampler"; break;
  case CL_INVALID_BINARY:                  errMsg = "Invalid binary"; break;
  case CL_INVALID_BUILD_OPTIONS:           errMsg = "Invalid build options"; break;
  case CL_INVALID_PROGRAM:                 errMsg = "Invalid program"; break;
  case CL_INVALID_PROGRAM_EXECUTABLE:      errMsg = "Invalid program executable"; break;
  case CL_INVALID_KERNEL_NAME:             errMsg = "Invalid kernel name"; break;
  case CL_INVALID_KERNEL_DEFINITION:       errMsg = "Invalid kernel definition"; break;
  case CL_INVALID_KERNEL:                  errMsg = "Invalid kernel"; break;
  case CL_INVALID_ARG_INDEX:               errMsg = "Invalid argument index"; break;
  case CL_INVALID_ARG_VALUE:               errMsg = "Invalid argument value"; break;
  case CL_INVALID_ARG_SIZE:                errMsg = "Invalid argument size"; break;
  case CL_INVALID_KERNEL_ARGS:             errMsg = "Invalid kernel arguments"; break;
  case CL_INVALID_WORK_DIMENSION:          errMsg = "Invalid work dimension"; break;
  case CL_INVALID_WORK_GROUP_SIZE:         errMsg = "Invalid work group size"; break;
  case CL_INVALID_WORK_ITEM_SIZE:          errMsg = "Invalid work item size"; break;
  case CL_INVALID_GLOBAL_OFFSET:           errMsg = "Invalid global offset"; break;
  case CL_INVALID_EVENT_WAIT_LIST:         errMsg = "Invalid event wait list"; break;
  case CL_INVALID_EVENT:                   errMsg = "Invalid event"; break;
  case CL_INVALID_OPERATION:               errMsg = "Invalid operation"; break;
  case CL_INVALID_GL_OBJECT:               errMsg = "Invalid OpenGL object"; break;
  case CL_INVALID_BUFFER_SIZE:             errMsg = "Invalid buffer size"; break;
  case CL_INVALID_MIP_LEVEL:               errMsg = "Invalid mip-map level"; break;
#ifndef __APPLE__
  case CL_PLATFORM_NOT_FOUND_KHR:          errMsg = "Platform not found"; break;
#endif

  case CL_INVALID_PROPERTY:                errMsg = "Invalid Property"; break;
  case CL_INVALID_IMAGE_DESCRIPTOR:        errMsg = "Invalid image descriptor"; break;
  case CL_INVALID_COMPILER_OPTIONS:        errMsg = "Invalid compiler options"; break;
  case CL_INVALID_LINKER_OPTIONS:          errMsg = "Invalid linker options"; break;
  case CL_INVALID_DEVICE_PARTITION_COUNT:  errMsg = "Invalid device partition count"; break;

    // extension errors
#ifndef __APPLE__
  case CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR: errMsg = "Invalid GL sharegroup reference"; break;
#endif
#if 0 // We don't need these yet, but I don't want to go digging if/when we do.
//#ifdef _MSC_VER
  case CL_INVALID_D3D10_DEVICE_KHR:            errMsg = "Invalid D3D10 Device"; break;
  case CL_INVALID_D3D10_RESOURCE_KHR:          errMsg = "Invalid D3D10 Resource"; break;
  case CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR: errMsg = "D3D10 Resource already acquired"; break;
  case CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR:     errMsg = "D3D10 Resource not acquired"; break;
#endif
  }

  return errMsg;
}

#  define CHECK_CL(fn, ...)                                             \
  do {                                                                  \
    cl_int err = fn(__VA_ARGS__);                                       \
    if(CL_SUCCESS != err) {                                             \
      const char *errMsg = clErrMsg(err);                               \
      if (NULL != errMsg) {                                             \
        fprintf(stderr, "OpenCL error (%s: %d): %s\n",                  \
                __FILE__, __LINE__, errMsg);                            \
      } else {                                                          \
        fprintf(stderr, "Unknown OpenCL error (%s: %d): %d\n",          \
                __FILE__, __LINE__, err);                               \
      }                                                                 \
      assert (false);                                                   \
    }                                                                   \
  } while(0)
#else
#  define CHECK_CL(fn, ...) do { (void)(fn(__VA_ARGS__)); } while(0)
#endif

#endif  // __GENTC_CL_GUARDS_H__

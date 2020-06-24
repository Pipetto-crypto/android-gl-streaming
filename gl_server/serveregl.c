// This file declare EGL methods on server side

#include "glserver.h"


void glse_eglBindAPI()
{
  GLSE_SET_COMMAND_PTR(c, eglBindAPI);
  EGLBoolean success = eglBindAPI(c->api);
  
  gls_ret_eglBindAPI_t *ret = (gls_ret_eglBindAPI_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglBindAPI;
  ret->success = success;
  glse_cmd_send_data(0,sizeof(gls_ret_eglBindAPI_t),(char *)glsec_global.tmp_buf.buf);
}

void glse_eglChooseConfig()
{
  GLSE_SET_COMMAND_PTR(c, eglChooseConfig);

  gls_data_egl_attriblist_t *dat = (gls_data_egl_attriblist_t *)glsec_global.tmp_buf.buf;
  gls_ret_eglChooseConfig_t *ret = (gls_ret_eglChooseConfig_t *)glsec_global.tmp_buf.buf;

  // EGLDisplay dpy = eglGetCurrentDisplay();
  EGLBoolean success = eglChooseConfig(c->dpy, dat->attrib_list, ret->configs, c->config_size, &ret->num_config);
  
  ret->success = success;

  // ret->configs = 

  // ret->success = EGL_TRUE;
  ret->cmd = GLSC_eglChooseConfig;
  glse_cmd_send_data(0,sizeof(gls_ret_eglChooseConfig_t),(char *)glsec_global.tmp_buf.buf);
}

void glse_eglCreateContext()
{
  GLSE_SET_COMMAND_PTR(c, eglCreateContext);
  gls_data_egl_attriblist_t *dat = (gls_data_egl_attriblist_t *)glsec_global.tmp_buf.buf;
  EGLContext context = eglCreateContext(c->dpy, c->config, c->share_list, dat->attrib_list);
  
  if (context != EGL_NO_CONTEXT) {
	  glsec_global.gc->context = context;
  }
  
  gls_ret_eglCreateContext_t *ret = (gls_ret_eglCreateContext_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglCreateContext;
  ret->context = context;
  glse_cmd_send_data(0, sizeof(gls_ret_eglCreateContext_t), (char *)glsec_global.tmp_buf.buf);
}

void glse_eglDestroyContext()
{
  GLSE_SET_COMMAND_PTR(c, eglDestroyContext);
  EGLBoolean success = eglDestroyContext(c->dpy, c->ctx);
  
  gls_ret_eglDestroyContext_t *ret = (gls_ret_eglDestroyContext_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglDestroyContext;
  ret->success = success;
  glse_cmd_send_data(0, sizeof(gls_ret_eglDestroyContext_t), (char *)glsec_global.tmp_buf.buf);
}

void glse_eglGetConfigAttrib()
{
  GLSE_SET_COMMAND_PTR(c, eglGetConfigAttrib);
  gls_ret_eglGetConfigAttrib_t *ret = (gls_ret_eglGetConfigAttrib_t *)glsec_global.tmp_buf.buf;
  
  // EGLDisplay dpy = eglGetCurrentDisplay();
  // c->config cause EGL_BAD_CONFIG error
  EGLBoolean success = eglGetConfigAttrib(c->dpy, c->config, c->attribute, &ret->value);
  
  ret->cmd = GLSC_eglGetConfigAttrib;
  ret->success = success;
  glse_cmd_send_data(0,sizeof(gls_ret_eglGetConfigAttrib_t),(char *)glsec_global.tmp_buf.buf);
}

void glse_eglGetConfigs()
{
  GLSE_SET_COMMAND_PTR(c, eglGetConfigs);
  gls_ret_eglGetConfigs_t *ret = (gls_ret_eglGetConfigs_t *)glsec_global.tmp_buf.buf;
  
  // EGLDisplay dpy = eglGetCurrentDisplay();
  EGLBoolean success = eglGetConfigs(c->dpy, ret->configs, c->config_size, &ret->num_config);
  
  ret->cmd = GLSC_eglGetConfigs;
  ret->success = success;
  glse_cmd_send_data(0,sizeof(gls_ret_eglGetConfigs_t),(char *)glsec_global.tmp_buf.buf);
}

void glse_eglGetCurrentContext()
{
  EGLContext context = eglGetCurrentContext();
  
  if (context != EGL_NO_CONTEXT) {
	  glsec_global.gc->context = context;
  }
  
  gls_ret_eglGetCurrentContext_t *ret = (gls_ret_eglGetCurrentContext_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglGetCurrentContext;
  ret->context = context;
  glse_cmd_send_data(0, sizeof(gls_ret_eglGetCurrentContext_t), (char *)glsec_global.tmp_buf.buf);
}

void glse_eglGetCurrentDisplay()
{
  EGLDisplay display = eglGetCurrentDisplay();

  if (display == EGL_NO_DISPLAY) {
	  display = glsec_global.gc->display;
  }

  gls_ret_eglGetCurrentDisplay_t *ret = (gls_ret_eglGetCurrentDisplay_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglGetCurrentDisplay;
  ret->display = display;
  glse_cmd_send_data(0, sizeof(gls_ret_eglGetCurrentDisplay_t), (char *)glsec_global.tmp_buf.buf);
}

void glse_eglGetCurrentSurface()
{
  GLSE_SET_COMMAND_PTR(c, eglGetCurrentSurface);
  EGLSurface surface = eglGetCurrentSurface(c->readdraw);
  
  if (surface != EGL_NO_SURFACE && c->readdraw == EGL_DRAW) {
	  glsec_global.gc->surface = surface;
  }
  
  gls_ret_eglGetCurrentSurface_t *ret = (gls_ret_eglGetCurrentSurface_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglGetCurrentSurface;
  ret->surface = surface;
  glse_cmd_send_data(0, sizeof(gls_ret_eglGetCurrentSurface_t), (char *)glsec_global.tmp_buf.buf);
}

void glse_eglGetError()
{
  GLuint error = eglGetError();
  // Should check gl error inside eglGetError() ???
  
  gls_ret_eglGetError_t *ret = (gls_ret_eglGetError_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglGetError;
  ret->error = error;
  glse_cmd_send_data(0, sizeof(gls_ret_eglGetError_t), (char *)glsec_global.tmp_buf.buf);
}

void glse_eglInitialize()
{
  GLSE_SET_COMMAND_PTR(c, eglInitialize);
  gls_ret_eglInitialize_t *ret = (gls_ret_eglInitialize_t *)glsec_global.tmp_buf.buf;
  EGLBoolean success = eglInitialize(c->dpy, &ret->major, &ret->minor);
  
  ret->cmd = GLSC_eglInitialize;
  ret->success = success;
  glse_cmd_send_data(0,sizeof(gls_ret_eglInitialize_t),(char *)glsec_global.tmp_buf.buf);
}

void glse_eglMakeCurrent()
{
  GLSE_SET_COMMAND_PTR(c, eglMakeCurrent);
  EGLBoolean success = eglMakeCurrent(c->dpy, c->draw, c->read, c->ctx);
  
  gls_ret_eglMakeCurrent_t *ret = (gls_ret_eglMakeCurrent_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglMakeCurrent;
  ret->success = success;
  glse_cmd_send_data(0, sizeof(gls_ret_eglMakeCurrent_t), (char *)glsec_global.tmp_buf.buf);
}

void glse_eglQueryContext()
{
  GLSE_SET_COMMAND_PTR(c, eglQueryContext);
  gls_ret_eglQueryContext_t *ret = (gls_ret_eglQueryContext_t *)glsec_global.tmp_buf.buf;
  
  EGLBoolean success = eglQueryContext(c->dpy, c->ctx, c->attribute, &ret->value);
  
  ret->cmd = GLSC_eglQueryContext;
  ret->success = success;
  glse_cmd_send_data(0,sizeof(gls_ret_eglQueryContext_t),(char *)glsec_global.tmp_buf.buf);
}

void glse_eglQueryString()
{
  GLSE_SET_COMMAND_PTR(c, eglQueryString);
  gls_ret_eglQueryString_t *ret = (gls_ret_eglQueryString_t *)glsec_global.tmp_buf.buf;
  
  const char *params = eglQueryString(c->dpy, c->name);
  
  ret->cmd = GLSC_eglQueryString;
  // LOGD("Client asking for %i, return %s", c->name, params);
  ret->params[GLS_STRING_SIZE_PLUS - 1] = '\0';
  strncpy(ret->params, params, GLS_STRING_SIZE);
  glse_cmd_send_data(0,sizeof(gls_ret_eglQueryString_t),(char *)glsec_global.tmp_buf.buf);
}

void glse_eglQuerySurface()
{
  GLSE_SET_COMMAND_PTR(c, eglQuerySurface);
  gls_ret_eglQuerySurface_t *ret = (gls_ret_eglQuerySurface_t *)glsec_global.tmp_buf.buf;
  
  EGLBoolean success = eglQuerySurface(c->dpy, c->surface, c->attribute, &ret->value);
  
  ret->cmd = GLSC_eglQuerySurface;
  ret->success = success;
  glse_cmd_send_data(0,sizeof(gls_ret_eglQuerySurface_t),(char *)glsec_global.tmp_buf.buf);
}

void glse_eglTerminate()
{
  GLSE_SET_COMMAND_PTR(c, eglTerminate);
  gls_ret_eglTerminate_t *ret = (gls_ret_eglTerminate_t *)glsec_global.tmp_buf.buf;
  ret->cmd = GLSC_eglTerminate;
  ret->success = eglTerminate(c->dpy);
  
  glse_cmd_send_data(0,sizeof(gls_ret_eglTerminate_t),(char *)glsec_global.tmp_buf.buf);
}

int egl_executeCommand(gls_command_t *c) {
	switch (c->cmd) {
        case GLSC_eglBindAPI:
			glse_eglBindAPI();
			break;
		case GLSC_eglChooseConfig:
			glse_eglChooseConfig();
			break;
		case GLSC_eglCreateContext:
			glse_eglCreateContext();
			break;
		case GLSC_eglGetConfigAttrib:
			glse_eglGetConfigAttrib();
			break;
		case GLSC_eglGetConfigs:
			glse_eglGetConfigs();
			break;
		case GLSC_eglGetCurrentContext:
			glse_eglGetCurrentContext();
			break;
		case GLSC_eglGetCurrentDisplay:
			glse_eglGetCurrentDisplay();
			break;
		case GLSC_eglGetCurrentSurface:
			glse_eglGetCurrentSurface();
			break;
        case GLSC_eglGetError:
			glse_eglGetError();
			break;
		case GLSC_eglInitialize:
			glse_eglInitialize();
			break;
        case GLSC_eglQueryContext:
			glse_eglQueryContext();
			break;
        case GLSC_eglQueryString:
			glse_eglQueryString();
			break;
        case GLSC_eglQuerySurface:
			glse_eglQuerySurface();
			break;
		case GLSC_eglTerminate:
			glse_eglTerminate();
			break;
/*
		case GLSC_eglXXX:
			glse_eglXXX();
			break:
*/
		default:
			return FALSE;
	}
	
	check_egl_err(c->cmd);
	return TRUE;
}

int egl_flushCommand(gls_command_t *c) {
	switch (c->cmd) {
		// Nothing here to flush
		default:
			return FALSE;
	}
	
	check_egl_err(c->cmd);
	return TRUE;
}


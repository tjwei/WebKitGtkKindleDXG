


#ifndef WEBKIT_ENUM_TYPES_H
#define WEBKIT_ENUM_TYPES_H

#include <glib-object.h>

#include <webkit/webkitdefines.h>

G_BEGIN_DECLS

#include <webkit/webkitdownload.h>

#define WEBKIT_TYPE_DOWNLOAD_STATUS webkit_download_status_get_type()

WEBKIT_API GType
webkit_download_status_get_type(void);

#define WEBKIT_TYPE_DOWNLOAD_ERROR webkit_download_error_get_type()

WEBKIT_API GType
webkit_download_error_get_type(void);

#include <webkit/webkiterror.h>

#define WEBKIT_TYPE_NETWORK_ERROR webkit_network_error_get_type()

WEBKIT_API GType
webkit_network_error_get_type(void);

#define WEBKIT_TYPE_POLICY_ERROR webkit_policy_error_get_type()

WEBKIT_API GType
webkit_policy_error_get_type(void);

#define WEBKIT_TYPE_PLUGIN_ERROR webkit_plugin_error_get_type()

WEBKIT_API GType
webkit_plugin_error_get_type(void);

#include <webkit/webkitwebframe.h>

#define WEBKIT_TYPE_LOAD_STATUS webkit_load_status_get_type()

WEBKIT_API GType
webkit_load_status_get_type(void);

#include <webkit/webkitwebnavigationaction.h>

#define WEBKIT_TYPE_WEB_NAVIGATION_REASON webkit_web_navigation_reason_get_type()

WEBKIT_API GType
webkit_web_navigation_reason_get_type(void);

#include <webkit/webkitwebview.h>

#define WEBKIT_TYPE_NAVIGATION_RESPONSE webkit_navigation_response_get_type()

WEBKIT_API GType
webkit_navigation_response_get_type(void);

#define WEBKIT_TYPE_WEB_VIEW_TARGET_INFO webkit_web_view_target_info_get_type()

WEBKIT_API GType
webkit_web_view_target_info_get_type(void);

G_END_DECLS

#endif



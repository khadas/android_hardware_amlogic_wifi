/*
 * WPA Supplicant / UNIX domain socket -based control interface
 * Copyright (c) 2004-2005, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef CTRL_IFACE_H
#define CTRL_IFACE_H

#ifdef CONFIG_CUSTOM_WFD
/* L2SD message type */
#define L2SDTA_MSG_TYPE_QUERY_OR_TRIGGER				1
#define L2SDTA_MSG_TYPE_SERVICE							2
#define L2SDTA_MSG_TYPE_ASSOC_STATUS					3
#define L2SDTA_MSG_TYPE_P2P_PROBE						4
#define L2SDTA_MSG_TYPE_WPS_STATUS              		5
#define WIDI_MSG_TYPE_P2P_WFD_IE                		8

/* L2SD Misc. MACRO */
#define L2SDTA_MAX_SSID_LEN            	32
#define L2SDTA_DEVICE_NAME_LEN         	32
#define L2SDTA_QUERY_TRIGGER_VE_LEN    	24
#define L2SDTA_PRIMARY_DEV_LEN         	8
#define L2SDTA_SERVICE_VE_LEN          	23
#define L2SDTA_DEVICE_PASSPHRASE_LEN	64
#define ETH_ALEN    6
#define L2SD_TYPE   					2
#define WIDI_CTRL_IFACE_PORT    		8888
#define WPS_FAIL_CHECK 					44
#define WPS_DEAUTHENTICATED				66

/* L2SD state */
#define L2SDTA_DISASSOCIATED                            0
#define L2SDTA_ASSOCIATED                               1
#define L2SDTA_WPS_STATUS_FAIL                          2
#define L2SDTA_WPS_STATUS_SUCCESS                       3
#define L2SDTA_DEAUTHENTICATED                          4

int hexstr2bin_WiDi(const char *hex, uint8_t  *buf, size_t len);
void  wpa_supplicant_ctrl_iface_scan_results_widi(struct wpa_supplicant *wpa_s);

struct l2sd_p2p_probe_wps_ie_msg_t {
	uint8_t src_mac[ETH_ALEN];
	uint8_t channel;
	uint8_t ssid_len;
	uint8_t ssid[L2SDTA_MAX_SSID_LEN];
	uint8_t category_id;
} __attribute__ ((packed));

struct l2sd_p2p_wfd_ie_msg_t {
	uint8_t type;
	uint8_t frame_type; // 1: probe req, 2: GO Nego Req, 3: GO Nego Confirm, 4: Provision Dicovery Req, 5: Invite Req
	uint8_t src_mac[ETH_ALEN];
	uint8_t dataLen;
	uint8_t data[0];
} __attribute__ ((packed));

struct l2sd_query_or_trig_msg_t
{
	uint8_t src_mac[ETH_ALEN];
	uint8_t channel;
	uint8_t ssid_len;
	uint8_t ssid[L2SDTA_MAX_SSID_LEN];
	uint8_t qa_ta_ext[L2SDTA_QUERY_TRIGGER_VE_LEN];
} __attribute__ ((packed));

struct l2sd_service_msg_t
{
	uint8_t dst_mac[ETH_ALEN];
	uint8_t channel;
	char sa_device_name[L2SDTA_DEVICE_NAME_LEN];
	uint8_t sa_primary_dev[L2SDTA_PRIMARY_DEV_LEN];
	uint8_t sa_ext[L2SDTA_SERVICE_VE_LEN];
} __attribute__ ((packed));

struct l2sd_assoc_msg_t
{
	uint8_t peer_mac[ETH_ALEN];
	uint8_t assoc_stat;
} __attribute__ ((packed));

struct l2sd_wps_status_msg_t
{
	uint8_t peer_mac[ETH_ALEN];
	uint8_t wps_status;
} __attribute__ ((packed));

struct l2sd_QCA_profile_sync_msg_t {
	uint8_t ssid[L2SDTA_MAX_SSID_LEN];
	uint8_t bssid[ETH_ALEN];	
	uint8_t passphrase[L2SDTA_DEVICE_PASSPHRASE_LEN];
} __attribute__ ((packed));

struct _l2_msg_t {
	uint8_t msg_type;
	union {		
		struct l2sd_p2p_probe_wps_ie_msg_t l2sd_p2p_probe_wps_ie_msg;
		struct l2sd_p2p_wfd_ie_msg_t l2sd_p2p_wfd_ie_msg;	
		struct l2sd_query_or_trig_msg_t l2sd_query_or_trig_msg;
		struct l2sd_service_msg_t l2sd_service_msg;
		struct l2sd_assoc_msg_t l2sd_assoc_msg;
		struct l2sd_wps_status_msg_t l2sd_wps_status_msg;
 		struct l2sd_QCA_profile_sync_msg_t l2sd_QCA_profile_sync_msg;	
	} __attribute__ ((packed)) u;
} __attribute__ ((packed));

typedef struct _l2_msg_t l2_msg_t;
#endif /* CONFIG_CUSTOM_WFD */

#ifdef CONFIG_CTRL_IFACE

/* Shared functions from ctrl_iface.c; to be called by ctrl_iface backends */

/**
 * wpa_supplicant_ctrl_iface_process - Process ctrl_iface command
 * @wpa_s: Pointer to wpa_supplicant data
 * @buf: Received command buffer (nul terminated string)
 * @resp_len: Variable to be set to the response length
 * Returns: Response (*resp_len bytes) or %NULL on failure
 *
 * Control interface backends call this function when receiving a message that
 * they do not process internally, i.e., anything else than ATTACH, DETACH,
 * and LEVEL. The return response value is then sent to the external program
 * that sent the command. Caller is responsible for freeing the buffer after
 * this. If %NULL is returned, *resp_len can be set to two special values:
 * 1 = send "FAIL\n" response, 2 = send "OK\n" response. If *resp_len has any
 * other value, no response is sent.
 */
char * wpa_supplicant_ctrl_iface_process(struct wpa_supplicant *wpa_s,
					 char *buf, size_t *resp_len);

/**
 * wpa_supplicant_ctrl_iface_process - Process global ctrl_iface command
 * @global: Pointer to global data from wpa_supplicant_init()
 * @buf: Received command buffer (nul terminated string)
 * @resp_len: Variable to be set to the response length
 * Returns: Response (*resp_len bytes) or %NULL on failure
 *
 * Control interface backends call this function when receiving a message from
 * the global ctrl_iface connection. The return response value is then sent to
 * the external program that sent the command. Caller is responsible for
 * freeing the buffer after this. If %NULL is returned, *resp_len can be set to
 * two special values: 1 = send "FAIL\n" response, 2 = send "OK\n" response. If
 * *resp_len has any other value, no response is sent.
 */
char * wpa_supplicant_global_ctrl_iface_process(struct wpa_global *global,
						char *buf, size_t *resp_len);


/* Functions that each ctrl_iface backend must implement */

/**
 * wpa_supplicant_ctrl_iface_init - Initialize control interface
 * @wpa_s: Pointer to wpa_supplicant data
 * Returns: Pointer to private data on success, %NULL on failure
 *
 * Initialize the control interface and start receiving commands from external
 * programs.
 *
 * Required to be implemented in each control interface backend.
 */
struct ctrl_iface_priv *
wpa_supplicant_ctrl_iface_init(struct wpa_supplicant *wpa_s);

/**
 * wpa_supplicant_ctrl_iface_deinit - Deinitialize control interface
 * @priv: Pointer to private data from wpa_supplicant_ctrl_iface_init()
 *
 * Deinitialize the control interface that was initialized with
 * wpa_supplicant_ctrl_iface_init().
 *
 * Required to be implemented in each control interface backend.
 */
void wpa_supplicant_ctrl_iface_deinit(struct ctrl_iface_priv *priv);

/**
 * wpa_supplicant_ctrl_iface_wait - Wait for ctrl_iface monitor
 * @priv: Pointer to private data from wpa_supplicant_ctrl_iface_init()
 *
 * Wait until the first message from an external program using the control
 * interface is received. This function can be used to delay normal startup
 * processing to allow control interface programs to attach with
 * %wpa_supplicant before normal operations are started.
 *
 * Required to be implemented in each control interface backend.
 */
void wpa_supplicant_ctrl_iface_wait(struct ctrl_iface_priv *priv);

/**
 * wpa_supplicant_global_ctrl_iface_init - Initialize global control interface
 * @global: Pointer to global data from wpa_supplicant_init()
 * Returns: Pointer to private data on success, %NULL on failure
 *
 * Initialize the global control interface and start receiving commands from
 * external programs.
 *
 * Required to be implemented in each control interface backend.
 */
struct ctrl_iface_global_priv *
wpa_supplicant_global_ctrl_iface_init(struct wpa_global *global);

/**
 * wpa_supplicant_global_ctrl_iface_deinit - Deinitialize global ctrl interface
 * @priv: Pointer to private data from wpa_supplicant_global_ctrl_iface_init()
 *
 * Deinitialize the global control interface that was initialized with
 * wpa_supplicant_global_ctrl_iface_init().
 *
 * Required to be implemented in each control interface backend.
 */
void wpa_supplicant_global_ctrl_iface_deinit(
	struct ctrl_iface_global_priv *priv);

#else /* CONFIG_CTRL_IFACE */

static inline struct ctrl_iface_priv *
wpa_supplicant_ctrl_iface_init(struct wpa_supplicant *wpa_s)
{
	return (void *) -1;
}

static inline void
wpa_supplicant_ctrl_iface_deinit(struct ctrl_iface_priv *priv)
{
}

static inline void
wpa_supplicant_ctrl_iface_send(struct ctrl_iface_priv *priv, int level,
			       char *buf, size_t len)
{
}

static inline void
wpa_supplicant_ctrl_iface_wait(struct ctrl_iface_priv *priv)
{
}

static inline struct ctrl_iface_global_priv *
wpa_supplicant_global_ctrl_iface_init(struct wpa_global *global)
{
	return (void *) 1;
}

static inline void
wpa_supplicant_global_ctrl_iface_deinit(struct ctrl_iface_global_priv *priv)
{
}

#endif /* CONFIG_CTRL_IFACE */

#endif /* CTRL_IFACE_H */

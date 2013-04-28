/*****************************************************************************/
/* \file ieee80211_external.h
** \brief External Header File References
**
**  This header file refers to the internal header files that provide the
**  data structure definitions and parameters required by external programs
**  that interface via ioctl or similiar mechanisms.  This hides the location
**  of the specific header files, and provides a control to limit what is
**  being exported for external use.
**
**  Copyright (c) 2009 Atheros Communications Inc.  All rights reserved.
**
** Permission to use, copy, modify, and/or distribute this software for any
** purpose with or without fee is hereby granted, provided that the above
** copyright notice and this permission notice appear in all copies.
**
** THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
** WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
** MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
** ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
** WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
** ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
** OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
**/


#ifndef IEEE80211_EXTERNAL_H
#define IEEE80211_EXTERNAL_H

#ifndef __packed
#define __packed    __attribute__((__packed__))
#endif
#define EXTERNAL_USE_ONLY

/*
** Key definitions moved to here to allow them to be published externally
** without having to export all of the other stuff.  These need to be consistent
** with the definitions in ieee80211_crypto.h
*/

#define	IEEE80211_KEY_XMIT	0x01	/* key used for xmit */
#define	IEEE80211_KEY_RECV	0x02	/* key used for recv */
#define	IEEE80211_KEY_GROUP	0x04	/* key used for WPA group operation */
#define IEEE80211_KEY_MFP   0x08    /* key also used for management frames */
#define	IEEE80211_KEY_SWCRYPT	0x10	/* host-based encrypt/decrypt */
#define	IEEE80211_KEY_SWMIC	0x20	/* host-based enmic/demic */
#define IEEE80211_KEY_PERSISTENT 0x40   /* do not remove unless OS commands us to do so */
#define IEEE80211_KEY_PERSTA    0x80    /* per STA default key */

#endif /* IEEE80211_EXTERNAL_H */

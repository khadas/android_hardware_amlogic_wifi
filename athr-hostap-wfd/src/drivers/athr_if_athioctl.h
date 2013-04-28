/*
 * Copyright (c) 2010, Atheros Communications Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * Ioctl-related defintions for the Atheros Wireless LAN controller driver.
 */
#ifndef _DEV_ATH_ATHIOCTL_H
#define _DEV_ATH_ATHIOCTL_H

#ifdef VOW_LOGLATENCY
#define ATH_STATS_LATENCY_BINS 45  /* Number of 1024us bins to log latency */
#define ATH_STATS_LATENCY_CATS 5     /* Number of categories to log latency: 4 access categories + 1 combined */
#endif

/*
 * 11n tx/rx stats
 */
struct ath_11n_stats {
    u_int32_t   tx_pkts;            /* total tx data packets */
    u_int32_t   tx_checks;          /* tx drops in wrong state */
    u_int32_t   tx_drops;           /* tx drops due to qdepth limit */
    u_int32_t   tx_minqdepth;       /* tx when h/w queue depth is low */
    u_int32_t   tx_queue;           /* tx pkts when h/w queue is busy */
    u_int32_t   tx_resetq;          /* tx reset queue instances */
    u_int32_t   tx_comps;           /* tx completions */
    u_int32_t   tx_comperror;       /* tx error completions on global failures */
    u_int32_t   tx_unaggr_comperror; /* tx error completions of unaggregted frames */
    u_int32_t   tx_stopfiltered;    /* tx pkts filtered for requeueing */
    u_int32_t   tx_qnull;           /* txq empty occurences */
    u_int32_t   tx_noskbs;          /* tx no skbs for encapsulations */
    u_int32_t   tx_nobufs;          /* tx no descriptors */
    u_int32_t   tx_badsetups;       /* tx key setup failures */
    u_int32_t   tx_normnobufs;      /* tx no desc for legacy packets */
    u_int32_t   tx_schednone;       /* tx schedule pkt queue empty */
    u_int32_t   tx_bars;            /* tx bars sent */
    u_int32_t   tx_legacy;          /* tx legacy frames sent */
    u_int32_t   txunaggr_single;    /* tx unaggregate singles sent */
    u_int32_t   txbar_xretry;       /* tx bars excessively retried */
    u_int32_t   txbar_compretries;  /* tx bars retried */
    u_int32_t   txbar_errlast;      /* tx bars last frame failed */
    u_int32_t   tx_compunaggr;      /* tx unaggregated frame completions */
    u_int32_t   txunaggr_xretry;    /* tx unaggregated excessive retries */
    u_int32_t   tx_compaggr;        /* tx aggregated completions */
    u_int32_t   tx_bawadv;          /* tx block ack window advanced */
    u_int32_t   tx_bawretries;      /* tx block ack window retries */
    u_int32_t   tx_bawnorm;         /* tx block ack window additions */
    u_int32_t   tx_bawupdates;      /* tx block ack window updates */
    u_int32_t   tx_bawupdtadv;      /* tx block ack window advances */
    u_int32_t   tx_retries;         /* tx retries of sub frames */
    u_int32_t   tx_xretries;        /* tx excessive retries of aggregates */
    u_int32_t   tx_aggregates;      /* tx aggregated pkts sent */
    u_int32_t   tx_sf_hw_xretries;  /* sub-frames excessively retried in h/w */
    u_int32_t   tx_aggr_frames;     /* tx total frames aggregated */
    u_int32_t   txaggr_noskbs;      /* tx no skbs for aggr encapsualtion */
    u_int32_t   txaggr_nobufs;      /* tx no desc for aggr */
    u_int32_t   txaggr_badkeys;     /* tx enc key setup failures */
    u_int32_t   txaggr_schedwindow; /* tx no frame scheduled: baw limited */
    u_int32_t   txaggr_single;      /* tx frames not aggregated */
    u_int32_t   txaggr_mimo;        /* tx frames aggregated for mimo */
    u_int32_t   txaggr_compgood;    /* tx aggr good completions */
    u_int32_t   txaggr_comperror;   /* tx aggr error completions */
    u_int32_t   txaggr_compxretry;  /* tx aggr excessive retries */
    u_int32_t   txaggr_compretries; /* tx aggr unacked subframes */
    u_int32_t   txunaggr_compretries; /* tx non-aggr unacked subframes */
    u_int32_t   txaggr_prepends;    /* tx aggr old frames requeued */
    u_int32_t   txaggr_filtered;    /* filtered aggr packet */
    u_int32_t   txaggr_fifo;        /* fifo underrun of aggregate */
    u_int32_t   txaggr_xtxop;       /* txop exceeded for an aggregate */
    u_int32_t   txaggr_desc_cfgerr; /* aggregate descriptor config error */
    u_int32_t   txaggr_data_urun;   /* data underrun for an aggregate */
    u_int32_t   txaggr_delim_urun;  /* delimiter underrun for an aggregate */
    u_int32_t   txaggr_errlast;     /* tx aggr: last sub-frame failed */
    u_int32_t   txunaggr_errlast;   /* tx non-aggr: last frame failed */
    u_int32_t   txaggr_longretries; /* tx aggr h/w long retries */
    u_int32_t   txaggr_shortretries;/* tx aggr h/w short retries */
    u_int32_t   txaggr_timer_exp;   /* tx aggr : tx timer expired */
    u_int32_t   txaggr_babug;       /* tx aggr : BA bug */
    u_int32_t   txrifs_single;      /* tx frames not bursted */
    u_int32_t   txrifs_babug;       /* tx rifs : BA bug */
    u_int32_t   txaggr_badtid;      /* tx aggr : Bad TID */
    u_int32_t   txrifs_compretries; /* tx rifs unacked subframes */
    u_int32_t   txrifs_bar_alloc;   /* tx rifs bars allocated */
    u_int32_t   txrifs_bar_freed;   /* tx rifs bars freed */
    u_int32_t   txrifs_compgood;    /* tx rifs good completions */
    u_int32_t   txrifs_prepends;    /* tx rifs old frames requeued */
    u_int32_t   tx_comprifs;        /* tx rifs completions */
    u_int32_t   tx_compnorifs;      /* tx not a rifs completion */
    u_int32_t   rx_pkts;            /* rx pkts */
    u_int32_t   rx_aggr;            /* rx aggregated packets */
    u_int32_t   rx_aggrbadver;      /* rx pkts with bad version */
    u_int32_t   rx_bars;            /* rx bars */
    u_int32_t   rx_nonqos;          /* rx non qos-data frames */
    u_int32_t   rx_seqreset;        /* rx sequence resets */
    u_int32_t   rx_oldseq;          /* rx old packets */
    u_int32_t   rx_bareset;         /* rx block ack window reset */
    u_int32_t   rx_baresetpkts;     /* rx pts indicated due to baw resets */
    u_int32_t   rx_dup;             /* rx duplicate pkts */
    u_int32_t   rx_baadvance;       /* rx block ack window advanced */
    u_int32_t   rx_recvcomp;        /* rx pkt completions */
    u_int32_t   rx_bardiscard;      /* rx bar discarded */
    u_int32_t   rx_barcomps;        /* rx pkts unblocked on bar reception */
    u_int32_t   rx_barrecvs;        /* rx pkt completions on bar reception */
    u_int32_t   rx_skipped;         /* rx pkt sequences skipped on timeout */
    u_int32_t   rx_comp_to;         /* rx indications due to timeout */
    u_int32_t   rx_timer_starts;    /* rx countdown timers started */
    u_int32_t   rx_timer_stops;     /* rx countdown timers stopped */ 
    u_int32_t   rx_timer_run;       /* rx timeout occurences */
    u_int32_t   rx_timer_more;      /* rx partial timeout of pending packets */
    u_int32_t   wd_tx_active;       /* watchdog: tx is active */
    u_int32_t   wd_tx_inactive;     /* watchdog: tx is not active */
    u_int32_t   wd_tx_hung;         /* watchdog: tx is hung */
    u_int32_t   wd_spurious;        /* watchdog: spurious tx hang */
    u_int32_t   tx_requeue;         /* filter & requeue on 20/40 transitions */
    u_int32_t   tx_drain_txq;       /* draining tx queue on error */
    u_int32_t   tx_drain_tid;       /* draining tid buf queue on error */
    u_int32_t   tx_cleanup_tid;     /* draining tid buf queue on node cleanup */
    u_int32_t   tx_drain_bufs;      /* buffers drained from pending tid queue */
    u_int32_t   tx_tidpaused;       /* pausing tx on tid */
    u_int32_t   tx_tidresumed;      /* resuming tx on tid */
    u_int32_t   tx_unaggr_filtered; /* unaggregated tx pkts filtered */
    u_int32_t   tx_aggr_filtered;   /* aggregated tx pkts filtered */
    u_int32_t   tx_filtered;        /* total sub-frames filtered */
    u_int32_t   rx_rb_on;           /* total rb-s on  */
    u_int32_t   rx_rb_off;          /* total rb-s off */
    u_int32_t   rx_dsstat_err;      /* rx descriptor status corrupted */
};

struct ath_phy_stats {
    u_int64_t   ast_tx_rts;   /* RTS success count */
    u_int64_t   ast_tx_shortretry;/* tx on-chip retries (short). RTSFailCnt */
    u_int64_t   ast_tx_longretry;/* tx on-chip retries (long). DataFailCnt */
    u_int64_t   ast_rx_tooshort;/* rx discarded 'cuz frame too short */
    u_int64_t   ast_rx_toobig;    /* rx discarded 'cuz frame too large */
    u_int64_t   ast_rx_err; /* rx error */
    u_int64_t   ast_rx_crcerr;    /* rx failed 'cuz of bad CRC */
    u_int64_t   ast_rx_fifoerr;    /* rx failed 'cuz of FIFO overrun */
    u_int64_t   ast_rx_phyerr;    /* rx PHY error summary count */
    u_int64_t   ast_rx_decrypterr; /* rx decryption error */
    u_int64_t   ast_rx_demicerr; /* rx demic error */
    u_int64_t   ast_rx_demicok; /* rx demic ok */
    u_int64_t   ast_rx_delim_pre_crcerr; /* pre-delimiter crc errors */
    u_int64_t   ast_rx_delim_post_crcerr; /* post-delimiter crc errors */
    u_int64_t   ast_rx_decrypt_busyerr; /* decrypt busy errors */
    u_int64_t   ast_rx_phy[32];    /* rx PHY error per-code counts */
};

struct ath_stats {
    u_int32_t    ast_watchdog;     /* device reset by watchdog */
    u_int32_t    ast_resetOnError; /* resets on error */
    u_int32_t    ast_hardware;     /* fatal hardware error interrupts */
    u_int32_t    ast_bmiss;        /* beacon miss interrupts */
    u_int32_t    ast_rxorn;        /* rx overrun interrupts */
    u_int32_t    ast_rxorn_bmiss;  /* rx overrun and bmiss interrupts: indicate descriptor corruption */
    u_int32_t    ast_rxeol;        /* rx eol interrupts */
    u_int32_t    ast_txurn;        /* tx underrun interrupts */
    u_int32_t    ast_txto;         /* tx timeout interrupts */
    u_int32_t    ast_cst;          /* carrier sense timeout interrupts */
    u_int32_t    ast_mib;          /* mib interrupts */
    u_int32_t    ast_rx;           /* rx interrupts */
    u_int32_t    ast_rxdesc;       /* rx descriptor interrupts */
    u_int32_t    ast_rxerr;        /* rx error interrupts */
    u_int32_t    ast_rxnofrm;      /* rx no frame interrupts */
    u_int32_t    ast_tx;           /* tx interrupts */
    u_int32_t    ast_txdesc;       /* tx descriptor interrupts */
    u_int32_t    ast_tim_timer;    /* tim timer interrupts */
    u_int32_t    ast_bbevent;      /* baseband event interrupts */
    u_int32_t    ast_rxphy;        /* rx phy error interrupts */
    u_int32_t    ast_rxkcm;        /* rx key cache miss interrupts */
    u_int32_t    ast_swba;         /* sw beacon alert interrupts */
    u_int32_t    ast_bnr;          /* beacon not ready interrupts */
    u_int32_t    ast_tim;          /* tim interrupts */
    u_int32_t    ast_dtim;         /* dtim interrupts */
    u_int32_t    ast_dtimsync;     /* dtimsync interrupts */
    u_int32_t    ast_gpio;         /* general purpose IO interrupts */
    u_int32_t    ast_cabend;       /* cab end interrupts */
    u_int32_t    ast_tsfoor;       /* tsf out-of-range interrupts */
    u_int32_t    ast_gentimer;     /* generic timer interrupts */
    u_int32_t    ast_gtt;          /* global transmit timeout interrupts */
    u_int32_t    ast_fatal;        /* fatal interrupts */
    u_int32_t    ast_tx_packets;   /* packet sent on the interface */
    u_int32_t    ast_rx_packets;   /* packet received on the interface */
    u_int32_t    ast_tx_mgmt;      /* management frames transmitted */
    u_int32_t    ast_tx_discard;   /* frames discarded prior to assoc */
    u_int32_t    ast_tx_invalid;   /* frames discarded 'cuz device gone */
    u_int32_t    ast_tx_qstop;     /* tx queue stopped 'cuz full */
    u_int32_t    ast_tx_encap;     /* tx encapsulation failed */
    u_int32_t    ast_tx_nonode;    /* tx failed 'cuz no node */
    u_int32_t    ast_tx_nobuf;     /* tx failed 'cuz no tx buffer (data) */
    u_int32_t    ast_tx_nobufmgt;  /* tx failed 'cuz no tx buffer (mgmt)*/
    u_int32_t    ast_tx_xretries;  /* tx failed 'cuz too many retries */
    u_int32_t    ast_tx_fifoerr;   /* tx failed 'cuz FIFO underrun */
    u_int32_t    ast_tx_filtered;  /* tx failed 'cuz xmit filtered */
    u_int32_t    ast_tx_badrate;   /* tx failed 'cuz bogus xmit rate */
    u_int32_t    ast_tx_noack;     /* tx frames with no ack marked */
    u_int32_t    ast_tx_cts;       /* tx frames with cts enabled */
    u_int32_t    ast_tx_shortpre;  /* tx frames with short preamble */
    u_int32_t    ast_tx_altrate;   /* tx frames with alternate rate */
    u_int32_t    ast_tx_protect;   /* tx frames with protection */
    u_int32_t    ast_rx_orn;       /* rx failed 'cuz of desc overrun */
    u_int32_t    ast_rx_badcrypt;  /* rx failed 'cuz decryption */
    u_int32_t    ast_rx_badmic;    /* rx failed 'cuz MIC failure */
    u_int32_t    ast_rx_nobuf;     /* rx setup failed 'cuz no skbuff */
        u_int32_t       ast_rx_hal_in_progress;
        u_int32_t       ast_rx_num_data;
        u_int32_t       ast_rx_num_mgmt;
        u_int32_t       ast_rx_num_ctl;
        u_int32_t       ast_rx_num_unknown;
        u_int32_t       ast_max_pkts_per_intr;
#define ATH_STATS_MAX_INTR_BKT  512
    u_int32_t   ast_pkts_per_intr[ATH_STATS_MAX_INTR_BKT+1]; /* counter bucket of packets handled in a single iteration */
    int8_t      ast_tx_rssi;                    /* tx rssi of last ack */
    int8_t      ast_tx_rssi_ctl0;               /* tx rssi of last ack [ctl, chain 0] */
    int8_t      ast_tx_rssi_ctl1;               /* tx rssi of last ack [ctl, chain 1] */
    int8_t      ast_tx_rssi_ctl2;               /* tx rssi of last ack [ctl, chain 2] */
    int8_t      ast_tx_rssi_ext0;               /* tx rssi of last ack [ext, chain 0] */
    int8_t      ast_tx_rssi_ext1;               /* tx rssi of last ack [ext, chain 1] */
    int8_t      ast_tx_rssi_ext2;               /* tx rssi of last ack [ext, chain 2] */
    int8_t      ast_rx_rssi;                    /* rx rssi from histogram [combined]*/
    int8_t      ast_rx_rssi_ctl0;               /* rx rssi from histogram [ctl, chain 0] */
    int8_t      ast_rx_rssi_ctl1;               /* rx rssi from histogram [ctl, chain 1] */
    int8_t      ast_rx_rssi_ctl2;               /* rx rssi from histogram [ctl, chain 2] */
    int8_t      ast_rx_rssi_ext0;               /* rx rssi from histogram [ext, chain 0] */
    int8_t      ast_rx_rssi_ext1;               /* rx rssi from histogram [ext, chain 1] */
    int8_t      ast_rx_rssi_ext2;               /* rx rssi from histogram [ext, chain 2] */
    u_int32_t   ast_be_xmit;                    /* beacons transmitted */
    u_int32_t   ast_be_nobuf;                    /* no skbuff available for beacon */
    u_int32_t   ast_per_cal;                    /* periodic calibration calls */
    u_int32_t   ast_per_calfail;                /* periodic calibration failed */
    u_int32_t   ast_per_rfgain;                    /* periodic calibration rfgain reset */
    u_int32_t   ast_rate_calls;                    /* rate control checks */
    u_int32_t   ast_rate_raise;                    /* rate control raised xmit rate */
    u_int32_t   ast_rate_drop;                    /* rate control dropped xmit rate */
    u_int32_t   ast_ant_defswitch;              /* rx/default antenna switches */
    u_int32_t   ast_ant_txswitch;               /* tx antenna switches */
    u_int32_t   ast_ant_rx[8];                    /* rx frames with antenna */
    u_int32_t   ast_ant_tx[8];                    /* tx frames with antenna */
    u_int64_t   ast_rx_bytes;                    /* total number of bytes received */
    u_int64_t   ast_tx_bytes;                    /* total number of bytes transmitted */
    u_int32_t   ast_rx_num_qos_data[16];        /* per tid rx packets (includes duplicates)*/
    u_int32_t   ast_rx_num_nonqos_data;         /* non qos rx packets    */
    u_int32_t   ast_txq_packets[16];            /* perq packets sent on the interface for each category */
    u_int32_t   ast_txq_xretries[16];           /* per q tx failed 'cuz too many retries */
    u_int32_t   ast_txq_fifoerr[16];            /* per q tx failed 'cuz FIFO underrun */
    u_int32_t   ast_txq_filtered[16];           /*per q  tx failed 'cuz xmit filtered */
    u_int32_t   ast_txq_athbuf_limit[16];       /* tx dropped 'cuz of athbuf limit */
    u_int32_t   ast_txq_nobuf[16];              /* tx dropped 'cuz no athbufs */
    u_int8_t    ast_num_rxchain;                /* Number of rx chains */
    u_int8_t    ast_num_txchain;                /* Number of tx chains */
    struct ath_11n_stats ast_11n_stats;         /* 11n statistics */
    u_int32_t   ast_bb_hang;                    /* BB hang detected */
    u_int32_t   ast_mac_hang;                   /* MAC hang detected */
#if ATH_WOW
    u_int32_t   ast_wow_wakeups;                /* count of hibernate and standby wakeups */
    u_int32_t   ast_wow_wakeupsok;              /* count of wakeups thru WoW */
    u_int32_t   ast_wow_wakeupserror;           /* count of errored wakeups */
#if ATH_WOW_DEBUG
    u_int32_t   ast_normal_sleeps;              /* count of normal sleeps */
    u_int32_t   ast_normal_wakeups;             /* count of normal wakeups*/
    u_int32_t   ast_wow_sleeps;                 /* count of wow sleeps */
    u_int32_t   ast_wow_sleeps_nonet;           /* w/o IP config */
#endif
#endif
#ifdef ATH_SUPPORT_UAPSD
    u_int32_t   ast_uapsdqnulbf_unavail;        /* no qos null buffers available */
    u_int32_t   ast_uapsdqnul_pkts;             /* count of qos null frames sent */
    u_int32_t   ast_uapsdtriggers;              /* count of UAPSD triggers received */
    u_int32_t   ast_uapsdnodeinvalid;           /* count of triggers for non-UAPSD node */
    u_int32_t   ast_uapsdeospdata;              /* count of QoS Data with EOSP sent */
    u_int32_t   ast_uapsddata_pkts;             /* count of UAPSD QoS Data frames sent */
    u_int32_t   ast_uapsddatacomp;              /* count of UAPSD QoS Data frames completed */
    u_int32_t   ast_uapsdqnulcomp;              /* count of UAPSD QoS NULL frames completed */
    u_int32_t   ast_uapsddataqueued;            /* count of UAPSD QoS Data Queued */
#endif
#ifdef ATH_SUPPORT_VOWEXT
    /* VOWEXT stats only. Literally some of the iqueue stats can be re-used here
     * As part of current release, all vow stats will be added extra and 
     * re-using will be thought for next release 
     */
    /*
     * ast_vow_ul_tx_calls : Number of frames Upper Layer ( ieee ) tried to send
     * over each access category. For each of the AC this would denote how many 
     * frames reached ATH layer.
     *                       
     * ast_vow_ath_txq_calls: Subset of ( ast_vow_ul_tx_calls ) that can be
     * either queued or can be sent immediate, either as an aggregate or as an
     * normal frame. This counts only frames that can be sent. 
    */
    u_int32_t   ast_vow_ul_tx_calls[4]; 
    u_int32_t   ast_vow_ath_txq_calls[4];
    u_int32_t   ast_vow_ath_be_drop, ast_vow_ath_bk_drop;
#endif
#if ATH_SUPPORT_CFEND
    u_int32_t ast_cfend_sched;			/* count of CF-END frames scheduled */
    u_int32_t ast_cfend_sent;   		/* count of CF-END frames sent */
#endif
#ifdef VOW_LOGLATENCY
    u_int32_t ast_retry_delay[ATH_STATS_LATENCY_CATS][ATH_STATS_LATENCY_BINS];
    u_int32_t ast_queue_delay[ATH_STATS_LATENCY_CATS][ATH_STATS_LATENCY_BINS];
#endif
};

/*
** Enumeration of parameter IDs
** This is how the external users refer to specific parameters, which is
** why it's defined in the external interface
*/

typedef enum {
    ATH_PARAM_TXCHAINMASK=1,
    ATH_PARAM_RXCHAINMASK,
    ATH_PARAM_TXCHAINMASKLEGACY,
    ATH_PARAM_RXCHAINMASKLEGACY,
    ATH_PARAM_CHAINMASK_SEL,
    ATH_PARAM_AMPDU,
    ATH_PARAM_AMPDU_LIMIT,
    ATH_PARAM_AMPDU_SUBFRAMES,
    ATH_PARAM_AGGR_PROT,
    ATH_PARAM_AGGR_PROT_DUR,
    ATH_PARAM_AGGR_PROT_MAX,
    ATH_PARAM_TXPOWER_LIMIT2G,
    ATH_PARAM_TXPOWER_LIMIT5G,
    ATH_PARAM_TXPOWER_OVERRIDE,
    ATH_PARAM_PCIE_DISABLE_ASPM_WK,
    ATH_PARAM_PCID_ASPM,
    ATH_PARAM_BEACON_NORESET,
    ATH_PARAM_CAB_CONFIG,
    ATH_PARAM_ATH_DEBUG,
    ATH_PARAM_ATH_TPSCALE,
    ATH_PARAM_ACKTIMEOUT,
#ifdef ATH_RB
    ATH_PARAM_RX_RB,
    ATH_PARAM_RX_RB_DETECT,
    ATH_PARAM_RX_RB_TIMEOUT,
    ATH_PARAM_RX_RB_SKIPTHRESH,
#endif
    ATH_PARAM_AMSDU_ENABLE,
#if ATH_SUPPORT_IQUE
    ATH_PARAM_RETRY_DURATION,
    ATH_PARAM_HBR_HIGHPER,
    ATH_PARAM_HBR_LOWPER,
#endif
    ATH_PARAM_RX_STBC,
    ATH_PARAM_TX_STBC,
    ATH_PARAM_LDPC,
    ATH_PARAM_LIMIT_LEGACY_FRM,
    ATH_PARAM_TOGGLE_IMMUNITY,
    ATH_PARAM_WEP_TKIP_AGGR_TX_DELIM,
    ATH_PARAM_WEP_TKIP_AGGR_RX_DELIM,
    ATH_PARAM_GPIO_LED_CUSTOM,
    ATH_PARAM_SWAP_DEFAULT_LED,
#if APPLE && ATH_SUPPORT_WIRESHARK
    ATH_PARAM_TAPMONITOR,
#endif
#if ATH_SUPPORT_VOWEXT
    ATH_PARAM_VOWEXT,
    ATH_PARAM_RCA, /* rate control and aggregation parameters */
	ATH_PARAM_VSP_ENABLE,
	ATH_PARAM_VSP_THRESHOLD,
	ATH_PARAM_VSP_EVALINTERVAL,
#endif
#if ATH_VOW_EXT_STATS
    ATH_PARAM_VOWEXT_STATS,
#endif
#ifdef VOW_TIDSCHED
    ATH_PARAM_TIDSCHED,
    ATH_PARAM_TIDSCHED_VOQW,
    ATH_PARAM_TIDSCHED_VIQW,
    ATH_PARAM_TIDSCHED_BKQW,
    ATH_PARAM_TIDSCHED_BEQW,
    ATH_PARAM_TIDSCHED_VOTO,
    ATH_PARAM_TIDSCHED_VITO,
    ATH_PARAM_TIDSCHED_BKTO,
    ATH_PARAM_TIDSCHED_BETO,
#endif
#if  ATH_SUPPORT_AOW
    ATH_PARAM_SW_RETRY_LIMIT,
    ATH_PARAM_AOW_LATENCY,
    ATH_PARAM_AOW_STATS,
    ATH_PARAM_AOW_LIST_AUDIO_CHANNELS,
    ATH_PARAM_AOW_PLAY_LOCAL,
    ATH_PARAM_AOW_CLEAR_AUDIO_CHANNELS,
    ATH_PARAM_AOW_ER,
    ATH_PARAM_AOW_EC,
    ATH_PARAM_AOW_EC_FMAP,
#endif  /* ATH_SUPPORT_AOW */
    /*Thresholds for interrupt mitigation*/
    ATH_PARAM_RIMT_FIRST,
    ATH_PARAM_RIMT_LAST,
    ATH_PARAM_TIMT_FIRST,
    ATH_PARAM_TIMT_LAST,
#ifdef VOW_LOGLATENCY
    ATH_PARAM_LOGLATENCY,
#endif
    ATH_PARAM_TXBF_SW_TIMER,
    ATH_PARAM_PHYRESTART_WAR,
    ATH_PARAM_CHANNEL_SWITCHING_TIME_USEC,
} ath_param_ID_t;

#define ATH_TX_POWER_SRM 0

#ifndef WIN32
struct ath_diag {
    char    ad_name[IFNAMSIZ];    /* if name, e.g. "ath0" */
    u_int16_t ad_id;
#define    ATH_DIAG_DYN    0x8000        /* allocate buffer in caller */
#define    ATH_DIAG_IN    0x4000        /* copy in parameters */
#define    ATH_DIAG_OUT    0x0000        /* copy out results (always) */
#define    ATH_DIAG_ID    0x0fff
    u_int16_t ad_in_size;        /* pack to fit, yech */
    caddr_t    ad_in_data;
    caddr_t    ad_out_data;
    u_int    ad_out_size;
};

#if APPLE
/* need to handle case where userland uses different sized
 * pointers than kernel, mostly x86_64 UL and 32-bit kernel
 */
struct ath_diag64 {
	char	    ad_name[IFNAMSIZ];                              /* 16 bytes */
	u_int16_t   ad_id;                                          /*  2 bytes */
	u_int16_t   ad_in_size;                                     /*  2 bytes */
	u_int64_t   ad_in_data __attribute__((aligned(8)));         /*  8 bytes */
	u_int64_t   ad_out_data;                                    /*  8 bytes */
	u_int	    ad_out_size;                                    /*  4 bytes */
};
#define SIOCGATHDIAG_64        _IOWR('i', 138, struct ath_diag64)
#define SIOCGATHTX99_64        _IOWR('i', 143, struct ath_diag64)

struct ath_diag32 {
	char	    ad_name[IFNAMSIZ];                              /* 16 bytes */
	u_int16_t   ad_id;                                          /*  2 bytes */
	u_int16_t   ad_in_size;                                     /*  2 bytes */
	u_int32_t   ad_in_data;                                     /*  4 bytes */
	u_int32_t   ad_out_data;                                    /*  4 bytes */
	u_int       ad_out_size;                                    /*  4 bytes */
};
#define SIOCGATHDIAG_32        _IOWR('i', 138, struct ath_diag32)
#define SIOCGATHTX99_32        _IOWR('i', 143, struct ath_diag32)
#endif

#define    ATH_RADAR_MUTE_TIME    1    /* Set dfs mute time for dfs test mode */

#ifdef __linux__
#define SIOCGATHSTATS       (SIOCDEVPRIVATE+0)
#define SIOCGATHDIAG        (SIOCDEVPRIVATE+1)
#define SIOCGATHCWMINFO     (SIOCDEVPRIVATE+2)
#define SIOCGATHCWMDBG      (SIOCDEVPRIVATE+3)
#define SIOCGATHSTATSCLR    (SIOCDEVPRIVATE+4)
#define SIOCGATHPHYERR      (SIOCDEVPRIVATE+5)
#define SIOCGATHEACS        (SIOCDEVPRIVATE+6)
#define SIOCGATHAOW         (SIOCDEVPRIVATE+8)

#define ATH_HAL_IOCTL_SETPARAM              (SIOCIWFIRSTPRIV+0)
#define ATH_HAL_IOCTL_GETPARAM              (SIOCIWFIRSTPRIV+1)
#define ATH_IOCTL_SETCOUNTRY                (SIOCIWFIRSTPRIV+2)
#define ATH_IOCTL_GETCOUNTRY                (SIOCIWFIRSTPRIV+3)

#define ATH_GET_COUNTRY                     1
#define ATH_SET_COUNTRY                     2

/*
** We have to do a "split" of ID values, since they are all combined
** into the same table.  This value is a "shift" value for ATH parameters
*/

#define ATH_PARAM_SHIFT     0x1000
#define SPECIAL_PARAM_SHIFT 0x2000

#else

struct ath_privreq {
    char        ap_name[IFNAMSIZ];    /* if_name, e.g. "wi0" */
    u_int16_t    ap_type;        /* req type */
    int16_t        ap_val;            /* Index or simple value */
    int16_t        ap_len;            /* Index or simple value */
    void        *ap_data;        /* Extra data */
};
#define SIOCATHPRIV        _IOWR('i', 140, struct ath_privreq)
#define SIOCGATHSTATS       _IOWR('i', 137, struct ifreq)
#define SIOCGATHDIAG        _IOWR('i', 138, struct ath_diag)
#define SIOCGATHCWMINFO     _IOWR('i', 139, struct ath_cwminfo)
#define SIOCGATHCWMDBG         _IOWR('i', 140, struct ath_cwmdbg)
#define SIOCGATHSTATSCLR    _IOWR('i', 141, struct ifreq)
#ifndef REMOVE_PKT_LOG
#define SIOCGATHPKT         _IOWR('i', 141, struct ath_pktlog_ioctl)
#endif /* REMOVE_PKT_LOG */
#define SIOCGATHPHYERR      _IOWR('i', 142, struct ath_diag)
#define SIOCGATHTX99        _IOWR('i', 143, struct ath_diag)
#define SIOCGATHEACS        _IOWR('i', 145, struct ifreq)


/*
 * packet_log support.
 */
#ifndef REMOVE_PKT_LOG
struct ieee80211com;
int ath_ioctl_pktlog(struct ieee80211com *, u_long, caddr_t);

struct ath_pktlog_ioctl {
    char    ap_name[IFNAMSIZ];    /* ifname, e.g. "ath0" */
    u_int16_t    ap_cmd;
    u_int32_t    ap_val;
    caddr_t    ap_data;
    u_int32_t    ap_data_size;
};

#if APPLE
struct ath_pktlog_ioctl64 {
    char	ap_name[IFNAMSIZ];	/* ifname, e.g. "ath0" */       /* 16 bytes */
    u_int16_t	ap_cmd;                                         /*  2 bytes */
    u_int32_t	ap_val;                                         /*  4 bytes */
    u_int64_t	ap_data __attribute__((aligned(8)));            /*  8 bytes */
    u_int32_t	ap_data_size;                                   /*  4 bytes */
};
#define SIOCGATHPKT_64         _IOWR('i', 141, struct ath_pktlog_ioctl64)

struct ath_pktlog_ioctl32 {
    char	ap_name[IFNAMSIZ];	/* ifname, e.g. "ath0" */       /* 16 bytes */
    u_int16_t	ap_cmd;                                         /*  2 bytes */
    u_int32_t	ap_val __attribute__((aligned(4)));             /*  4 bytes */
    u_int32_t	ap_data;                                        /*  4 bytes */
    u_int32_t	ap_data_size;                                   /*  4 bytes */
};
#define SIOCGATHPKT_32         _IOWR('i', 141, struct ath_pktlog_ioctl32)
#endif

#define    ATH_PKT_ENABLE        1
#define    ATH_PKT_SETSIZE       2
#define    ATH_PKT_READ          3 /* Kept for compatibility with the old code */
#define    ATH_PKT_RESET         4
#define    ATH_PKT_GETSIZE       5
#define    ATH_PKT_GETBUF        6
#define    ATH_PKT_GET_LOGSTATE  7

#endif /* REMOVE_PKT_LOG */

#endif

#endif
#endif /* _DEV_ATH_ATHIOCTL_H */


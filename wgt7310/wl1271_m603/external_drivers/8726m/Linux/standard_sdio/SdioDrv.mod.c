#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xc8a5d2b9, "module_layout" },
	{ 0x46be64e2, "kmalloc_caches" },
	{ 0x924f2350, "sdio_io_rw_extended" },
	{ 0xfdaf9eee, "dev_set_drvdata" },
	{ 0xa3544fb8, "sdio_enable_func" },
	{ 0x9de636e4, "sdio_claim_irq" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0xd08f305e, "sdio_change_ins" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xea147363, "printk" },
	{ 0x42224298, "sscanf" },
	{ 0xa9619f8c, "sdio_unregister_driver" },
	{ 0x1969fe83, "kmem_cache_alloc" },
	{ 0x7856b130, "sdio_release_irq" },
	{ 0xc27487dd, "__bug" },
	{ 0x37a0cba, "kfree" },
	{ 0x7498bdcf, "sdio_io_rw_direct" },
	{ 0x591c76ad, "sdio_register_driver" },
	{ 0x955fa1cb, "sdio_claim_host" },
	{ 0x4b519d7e, "dev_get_drvdata" },
	{ 0x2a3b9f93, "sdio_set_block_size" },
	{ 0xd87f4288, "sdio_disable_func" },
	{ 0xeb44d18f, "sdio_release_host" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "6BD19D95C62A53923B37C60");

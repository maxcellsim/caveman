/*
 * Project Caveman: VLink (Zero-Copy PCIe NTB Driver)
 * Bypassing the Linux Network Stack for Direct Memory Access.
 */

#include <linux/module.h>
#include <linux/ntb.h>
#include <linux/pci.h>

#define DRIVER_NAME "caveman_vlink"

struct caveman_device {
    struct ntb_dev *ntb;
    void __iomem *mw_base; // Remote Memory Window Base
    resource_size_t mw_size;
};

/* 
 * Map the Peer Node's LPDDR5X into local Address Space.
 * This turns the cluster into a single Unified Memory Entity.
 */
static int caveman_probe(struct ntb_client *client, struct ntb_dev *ntb) {
    struct caveman_device *cv;
    int res;

    cv = devm_kzalloc(&ntb->dev, sizeof(*cv), GFP_KERNEL);
    if (!cv) return -ENOMEM;

    cv->ntb = ntb;
    
    // Set up Memory Window 0 for Tidal Flow Activations
    res = ntb_mw_get_align(ntb, 0, NULL, &cv->mw_size, NULL);
    cv->mw_base = ntb_mw_map(ntb, 0);

    if (IS_ERR(cv->mw_base)) {
        pr_err("Caveman VLink: Failed to map Peer RAM window.\n");
        return PTR_ERR(cv->mw_base);
    }

    pr_info("Caveman VLink: Sovereign Link Established. Window Size: %llu bytes\n", cv->mw_size);
    return 0;
}

static struct ntb_client caveman_client = {
    .driver.name = DRIVER_NAME,
    .ops.probe = caveman_probe,
};

module_ntb_client(caveman_client);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Project Caveman Architects");
MODULE_DESCRIPTION("Bypassing TCP/IP for Sovereign Memory Scaling");

// SPDX-License-Identifier: GPL-2.0-only
/*
 * UFS PHY driver data for Exynos990 SoC
 *
 * Copyright (C) 2025 Igor Belwon <igor.belwon@mentallysanemainliners.org>
 */

#include "phy-samsung-ufs.h"

#define EXYNOS990_PHY_CTRL			0x724
#define EXYNOS990_PHY_CTRL_MASK			0x1
#define EXYNOS990_PHY_CTRL_EN			BIT(0)
#define EXYNOS990_COMBO_PHY_CDR_LOCK_STATUS 	0x7f
#define PHY_EXYNOS990_LANE_OFFSET		0x800

#define PHY_PMA_TRSV_ADDR(reg, lane)	(PHY_APB_ADDR((reg) + \
					((lane) * PHY_EXYNOS990_LANE_OFFSET)))

#define PHY_TRSV_REG_CFG_EXYNOS990(o, v, d) \
	PHY_TRSV_REG_CFG_OFFSET(o, v, d, PHY_EXYNOS990_LANE_OFFSET)

/* Calibration for phy initialization */
static const struct samsung_ufs_phy_cfg exynos990_pre_init_cfg[] = {
	PHY_COMN_REG_CFG(0x043, 0x10, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x046, 0x48, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x207, 0x0c, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2e1, 0x40, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x25d, 0x3f, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x25e, 0x36, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x25f, 0xdb, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x264, 0x4e, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x26e, 0x5e, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x26f, 0x70, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2ed, 0x25, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2ac, 0x23, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x279, 0xf0, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x273, 0x03, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2f4, 0x2f, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2b3, 0x05, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2b6, 0x0b, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2b7, 0x0b, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2b8, 0x0b, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2b9, 0x0b, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2ba, 0x0b, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2bb, 0x06, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2bc, 0x06, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2bd, 0x06, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2be, 0x06, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x307, 0x21, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x274, 0x50, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x234, 0x60, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2e4, 0x21, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x043, 0x18, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x043, 0x00, PWR_MODE_ANY),
	END_UFS_PHY_CFG,
};

static const struct samsung_ufs_phy_cfg exynos990_pre_pwr_hs_config[] = {
	PHY_TRSV_REG_CFG_EXYNOS990(0x2f2, 0x3f, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x246, 0x03, PWR_MODE_ANY),
	END_UFS_PHY_CFG
};

/* Calibration for HS mode series A/B */
static const struct samsung_ufs_phy_cfg exynos990_post_pwr_hs_config[] = {
	PHY_TRSV_REG_CFG_EXYNOS990(0x246, 0x01, PWR_MODE_ANY),
	END_UFS_PHY_CFG,
};

static const struct samsung_ufs_phy_cfg *exynos990_ufs_phy_cfgs[CFG_TAG_MAX] = {
	[CFG_PRE_INIT]		= exynos990_pre_init_cfg,
	[CFG_PRE_PWR_HS]	= exynos990_pre_pwr_hs_config,
	[CFG_POST_PWR_HS]	= exynos990_post_pwr_hs_config,
};

static const char * const exynos990_ufs_phy_clks[] = {
	"ref_clk",
};

const struct samsung_ufs_phy_drvdata exynos990_ufs_phy = {
	.cfgs = exynos990_ufs_phy_cfgs,
	.isol = {
		.offset = EXYNOS990_PHY_CTRL,
		.mask = EXYNOS990_PHY_CTRL_MASK,
		.en = EXYNOS990_PHY_CTRL_EN,
	},
	.clk_list = exynos990_ufs_phy_clks,
	.num_clks = ARRAY_SIZE(exynos990_ufs_phy_clks),
	.cdr_lock_status_offset = EXYNOS990_COMBO_PHY_CDR_LOCK_STATUS,
	.wait_for_cdr = samsung_ufs_phy_wait_for_lock_acq,
};

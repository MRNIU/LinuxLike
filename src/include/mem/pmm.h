
// This file is a part of Simple-XX/SimpleKernel
// (https://github.com/Simple-XX/SimpleKernel).
//
// pmm.h for Simple-XX/SimpleKernel.

#ifndef _PMM_H_
#define _PMM_H_

#include "stddef.h"
#include "stdint.h"
#include "io.h"
#include "e820.h"
#include "common.h"
#include "firstfit.h"

class PMM {
private:
    static IO io;
    // 可用内存的物理页数组
    static COMMON::physical_pages_t phy_pages[COMMON::PMM_PAGE_MAX_SIZE];
    // NORMAL 区域
    static size_t   normal_pages;
    static FIRSTFIT normal;
    // HIGH 区域
    static size_t   high_pages;
    static FIRSTFIT high;
    // 物理内存总数
    static size_t    pages;
    static FIRSTFIT *zone[COMMON::ZONE_COUNT];
    // 从 GRUB 读取物理内存信息
    void get_ram_info(e820map_t *e820map);
    // 物理内存管理初始化
    void mamage_init(void);

protected:
public:
    PMM(void);
    ~PMM(void);
    // 初始化内存管理
    int32_t init(void);
    // 请求指定 zone 的物理页
    void *alloc_page(uint32_t _pages, COMMON::zone_t _zone);
    // 释放内存页
    void free_page(void *_addr, uint32_t _pages, COMMON::zone_t _zone);
    // 获取空闲内存页数量
    uint32_t free_pages_count(COMMON::zone_t _zone);
};

#endif /* _PMM_H_ */

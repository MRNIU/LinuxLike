
// This file is a part of Simple-XX/SimpleKernel
// (https://github.com/Simple-XX/SimpleKernel).
//
// firstfit.h for Simple-XX/SimpleKernel.

#ifndef _FIRTSTFIT_H_
#define _FIRTSTFIT_H_

#include "stdint.h"
#include "io.h"

// TODO: 面向对象重构
class ff_list_entry_t {
public:
    // 当前页的地址
    uint8_t *addr;
    // 拥有多少个连续的页
    uint32_t npages;
    // 物理页被引用的次数
    int32_t ref;
    // 当前页状态
    uint32_t         flag;
    ff_list_entry_t *next;
    ff_list_entry_t *prev;
};

class FIRSTFIT {
private:
    static constexpr const uint32_t FF_USED   = 0x00;
    static constexpr const uint32_t FF_UNUSED = 0x01;

    static IO io;
    // 物理内存页的总数量
    static uint32_t phy_page_count;
    // 物理内存页的当前数量
    static uint32_t phy_page_free_count;
    // 空闲链表的节点数量
    static uint32_t node_num;
    // 内存管理
    static ff_list_entry_t    list[COMMON::PMM_PAGE_MAX_SIZE];
    COMMON::physical_pages_t &phy_pages;
    void set_chunk(ff_list_entry_t &chunk, COMMON::physical_pages_t &mempage,
                   size_t _idx);

protected:
public:
    FIRSTFIT(COMMON::physical_pages_t &_phy_pages);
    ~FIRSTFIT(void);
    // 初始化
    int32_t init(uint32_t pages);
    // 按页分配
    void *alloc(size_t pages);
    // 按页释放
    void free(void *addr, size_t pages);
    // 空闲页数量
    size_t free_pages_count(void);
};

#endif /* _FIRTSTFIT_H_ */

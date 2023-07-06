# MySnakeGame

> 23夏程序设计实践大作业

## 实现思路:

- 游戏地图以block为单元, 蛇和食物等通过指针指向block来标记其位置
- 渲染游戏界面时也以block为单位进行
- 待续

## 可选的待实现功能:

- 丰富的地形: 墙, 有穿越条件的障碍, 加速轨道, 机关
- 更多食物/触发物: 加生命, 短暂无敌, 时间减慢, 缩短蛇身
- 更多血量和血量奖惩
- 蛇吞: 收纳和吐出物品的能力/吐出物品攻击/吐出食物控制长度
- 多关卡
- 六边形地图(不好分辨?)
- 解密模式: 蛇一步一动, 需要通过触发机关通关
  - 颜色解密: 蛇有颜色属性, 颜色相关的机关, 改变颜色的食物, 改变机关颜色的物品
  - 传送门/传送门枪
  - 文字游戏: 蛇身体由字母组成, 食物也是字母, 吃下食物其字母增加到蛇尾, 拼成完整单词加分
- 战斗系统:
  - 机制boss
  - 蓄力撞击能力(需要一步一动), 吐出物品攻击, 将敌人围住来绞杀
  - pvp?
- 其他:
  - 可选模式的初始界面
  - 蛇的信息显示
  - 蛇罗斯方块: 吃食物时蛇"蜕皮"产生一个与蛇身相同形状的俄罗斯方块并坠落到地图最下方

## 基础类的实现说明

### blocks

继承关系: 

- ``BaseBlock``
  - ``Wall``

**BlockType:** 强枚举类, 用于标记block的类型, 每个类都不同

#### BaseBlock:

> 以下类似格式的说明中, private/public 等关键字仅说明紧随着的成员变量为该类型, 而出现的成员函数默认为 public

- private: 
  - ``BlockType TYPE`` 标记block的类型, 在每个子类中都有
    - ``type()`` 方法将被每个子类重载, 返回TYPE
  - ``string displayString`` 储存渲染用的字符串
    - ``toString()``
    - ``setString(string)``
- protected: 
  - ``int x, y`` 储存方块位置坐标
    - ``get_x()`` | ``get_y()``
  - ``BaseItem* ptrItem`` 指向非SnakeBody的item实例
  - ``SnakeBody* ptrSnakeBody`` 指向SnakeBody实例

> **正常情况下, block和在其上的item(包括SnakeBody)应该指向彼此! 双箭头!**

### items

继承关系:

- ``BaseItem``
  - ``Food``
  - ``Heart``
  - ``SnakeBody``

**ItemType:** 强枚举类, 用于标记item的类型, 每个类都不同

#### BaseItem:

- private:
  - ``ItemType TYPE`` 同block中的TYPE
  - ``string displayString`` 同block
- protected:
  - ``BaseBlock* ptrBlock`` 指向block实例
    - ``get_x()`` ``get_y()``
    - ``get_block()`` 返回指针
    - ``set_block(BaseBlock*)`` **不应该由用户使用!** 应使用    ``BaseBlock::set_item(...)`` 或 ``BaseBlock::attachSnakeBody(...)``


# 代码结构说明

更新于 `2023/5/21 17:30`

> 注意: 以下代码文件均位于[`../PlaneFight`](../PlaneFight)处, 位于同一文件夹中. 以下结构是`VS`解决方案中代码虚拟层次结构, 不代表文件夹中实际位置. 打开`VS`解决方案资源管理器即可看到这一个由"筛选器"(`Filter`)组成的结构. 

## `Form Files`

> `.ui`文件均存于此处. 用于编辑界面(虽然基本都是图片, 没怎么用过这些), 在`Qt Designer`中打开(`VS`中需特别设置在`Qt Designer`中打开). 

- `BattleField.ui`

## `Header Files` & `Source Files`

> 各种头文件/源文件. 除`main.cpp`外, 余下`*.h`与`*.cpp`一一对应. 两者结构一致, 故不分开讨论. 

### `Base`

> 各种抽象基类(接口). 这些抽象类都给出了具体子类以供参考. 

- `_Effect.h`&`_Effect.cpp` 实现了特殊效果的基类`_Effect`. 
    - 子类需要实现:
        ```cpp
        void display(QPainter& painter);
        ```
- `_Plane.h`&`_Plane.cpp` 实现了飞机的基类`_Plane`. 
    - 子类需要实现: 
        ```cpp
        void shootMissiles();
        void _setPosition(int __x, int __y); (protected)
        ```
- `_Missile.h`&`_Missle.cpp` 实现了子弹的基类`_Missile`.
    - 子类需要实现: 
        ```cpp
        void updatePosition();
        void hurt(_Plane* plane);
        QPolygon box() const; // 碰撞箱
        ```

### `Effect`

> 继承自基类`_Effect`的全体子类

- `ExplosionEffect.h`&`ExplosionEffect.cpp` 实现了爆炸特效(图像). 

### `Plane`

> 继承自基类`_Plane`的全体子类

- `PlayerPlane.h`&`PlayerPlane.cpp` 实现了玩家飞机
    - 这是一个**单例**模式(`Singleton`), 即只有一个可用对象, 通过静态成员函数调用: 
        ```cpp
        static PlayerPlane* PlayerPlane::plane();
        ```
    - 构造函数设为私有, 复制构造、赋值均已被**显式删除**, 不允许调用. 
    - 由于`Qt`要求`QPixmap`不得在界面进入前初始化, 对象默认是空. 初始化与删除需调用
        ```cpp
        static void PlayerPlane::init(); // new
        static void PlayerPlane::free(); // delete and changed to nullptr
        ```
- `EnemyPlane.h`&`EnemyPlane.cpp` 实现了: 
    - 敌机基类`EnemyPlane`. 它继承自`_Plane`, 但仍为抽象类. 要求子类实现: 
        ```cpp
        void updatePosition(); 
        ```
        子类可选择实现
        ```cpp
        void _setPosition(int __x, int __y); (protected)
        ```
    - 普通敌机`TrivialEnemyPlane`. 它继承自`EnemyPlane`. 
        - 位置更新策略: 竖直方向上匀速, 水平方向随机移动. 

### `Missile`

> 继承自基类`_Missile`的全体子类

- `SteadyMissile.h`&`SteadyMissile.cpp` 实现了匀速运动的子弹

### `UI`

> 继承自`QWidget`等窗口类的子类, 负责界面

- `BattleField.h`&`BattleField.cpp` 实现了战场主界面

### `Util`

> 配置文件及好用的小函数

#### `config.h`&`config.cpp`

> 配置文件, **全项目通用**的数值常量等在此定义. **仅在单个文件使用**的变量最好在文件开头声明并定义为`static constexpr T t = ...`, 不要污染全局. 

#### `util.h`&`util.cpp`

> 有一些好用的小函数或结构体. 

### `main.cpp`

现在处于测试阶段, 随意更改, 对已完成部分测试. 
希望最终不要在`main.cpp`中写大量代码. 

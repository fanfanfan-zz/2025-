
# ROS 节点通信学习笔记

这个软件包是我用来学习 ROS 中的节点通信的，其中包含了两个节点：
- **发布者节点**：`wang_node`
- **订阅者节点**：`ma_node`

另外，还创建了一个 `launch` 文件，用于启动这两个节点。

该md文件则是作为一个笔记，记录了我在编写这个软件包的过程中所学到的知识。

---

## 1. CMakeLists.txt 文件编写

在编写 `CMakeLists.txt` 文件时，需要注意以下几点：

### 1.1 添加可执行文件
需要将编译生成的可执行文件添加到可执行文件列表中，否则在编译时会出现找不到可执行文件的问题。

示例代码：
```cmake
add_executable(wang_node src/wang_node.cpp)
```

### 1.2 链接 ROS 库文件
需要将 ROS 所需的库文件链接到可执行文件中，否则在运行时会出现找不到库文件的问题。

示例代码：
```cmake
target_link_libraries(wang_node ${catkin_LIBRARIES})
```

### 1.3 添加依赖
确保编译时依赖的其他目标（如消息生成目标）已经完成。

示例代码：
```cmake
add_dependencies(wang_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
```

---

## 2. Launch 文件编写

在编写 `launch` 文件时，可以使用 `launch-prefix` 来启动一个新的终端窗口。

示例代码：
```xml
<node pkg="ssr_pkg_1" type="wang_node" name="wang_node" launch-prefix="gnome-terminal --"/>
```

---

## 3. 回调函数与智能指针

在编写回调函数时，可以使用共享指针（`std::shared_ptr`）来避免在回调函数中创建新的对象。这样可以提高效率，并避免内存泄漏等问题。


---

## 4. 控制节点运行频率

### 4.1 使用 `ros::Rate` 类
`ros::Rate` 类用于控制节点的运行频率，避免节点运行过快导致系统资源紧张。

示例代码：
```cpp
ros::Rate rate(10); // 10 Hz
while (ros::ok()) {
    // 节点逻辑
    rate.sleep();
}
```

### 4.2 使用 `ros::Duration` 类
`ros::Duration` 类用于控制节点的休眠时间。将 `ros::Rate` 和 `ros::Duration` 结合使用，可以更好地控制节点的运行频率。

示例代码：
```cpp
ros::Duration(1.0).sleep(); // 休眠 1 秒
```

---

## 总结

通过这个软件包的开发，我学习了以下内容：
1. 如何正确编写 `CMakeLists.txt` 文件，确保可执行文件和库文件的正确编译和链接。
2. 如何使用 `launch` 文件启动节点，并通过 `launch-prefix` 在新终端中运行节点。
3. 如何使用共享指针编写高效的回调函数，避免内存泄漏。
4. 如何使用 `ros::Rate` 和 `ros::Duration` 控制节点的运行频率和休眠时间。



---

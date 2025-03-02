iMonitor（冰镜 - 终端行为分析系统）是一款基于[iMonitorSDK](https://github.com/wecooperate/iMonitorSDK)的开源终端行为监控分析软件。

提供了对进程、文件、注册表、网络等系统行为的监控。支持扩展和脚本，可以轻易定制和添加更多功能。可以用于病毒分析、软件逆向、入侵检测，EDR等。

## 一些特点

-   开源
-   支持Win7到Win11的32位、64位系统（因为Qt用了比较新的版本不支持XP了，需要支持的可以自行换成支持XP的Qt版本）
-   支持丰富的行为监控，支持进程打开事件、支持socket的各种操作事件
-   支持按每个事件字段的过滤条件，支持堆栈模块的过滤条件
-   **所有iMonitor监控到的行为，都可以通过[iMonitorSDK](https://github.com/wecooperate/iMonitorSDK)、[iDefender](https://github.com/wecooperate/iDefender)来拦截阻止**
-   **支持脚本化和应用市场，可以无限扩展和定制功能（待支持）**
-   **多方平台集成（待支持）**

## 源码编译

-   需要VS2019及以上环境
-   需要CMake 3.10 之后的版本
-   需要安装Qt5.12（默认支持多语言，需要同时安装qtlinguistinstaller）
-   执行目录下的build.bat即可 （此步骤会提示设置QT的安装路径，按提示设置环境变量）

## 软件截图

![normal](./doc/normal.png)

事件详情
![](./doc/bin.png)
![process](./doc/process.png)
![callstack](./doc/callstack.png)

Win11
![color](./doc/color.png)

## 后续计划

- 基本功能完善

  - [ ] 支持数据的保存、加载
  - [ ] 支持规则的保存、规则列表
  - [ ] 支持进程、文件、注册表、网络的信息汇总
  - [ ] 支持搜索、快速过滤、标签
  - [ ] 列支持自定义、编辑、显示隐藏
  - [ ] 完善QSS、国际化
- 插件扩展

  - [ ] 支持插件扩展
  - [ ] 支持脚本扩展
  - [ ] 关键插件
    - [ ] 过滤插件：支持更加复杂的条件过滤
    - [ ] 显示插件：添加更多的信息展示
    - [ ] 行为插件：可以分析每一个路径的含义
    - [ ] 安全插件：根据行为的权值，智能分析出病毒行为
    - [ ] 逆向插件：自动过滤掉系统路径，快速分析一个软件存储修改哪些数据
  - [ ] 开发平台 - 应用市场的支持
- 检测分析与响应

  - [ ] 结合iDefender主动防御系统，快速禁用检测到的行为
  - [ ] 数据支持上报集成到EDR、SOC、SIEM等平台

## 关于我们

优秀的人，做专业的事。

创信长荣科技是一家致力于为企业管理提供基础服务、一体化管理平台，力争成为企业管理入口，促进企业管理标准化、数字化的企业。我们的目标是拒绝内卷，让每个人更好的工作和生活。

我们的成员是来自金山、360、腾讯等企业的顶级优秀人才，具备深厚的技术水平。多款核心产品正在研发中，需要各方面的人才和资本投入。

[联系我们](mailto://iMonitor@qq.com)

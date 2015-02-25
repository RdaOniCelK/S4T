# S4T
script for test. use to design an user-defined script language and parser

2013年4月份开发的,当初目的是想实现一个简单的脚本语言来执行测试方案,故取名"S4T"(Script for Test);
当时做了一个月后就一直搁置了,现在拿出来开源,跟大家学习交流;
目前只实现了词法与语法的分析.其中词法分析的代码是固定的,语法分析代码是根据用户定义的语法图由代码生成子工程(CodeGenerate)生成.

# 建表文件（最终）
CREATE TABLE `order_list` (
  `OrderID` int NOT NULL AUTO_INCREMENT,
  `OrderDate` date DEFAULT NULL COMMENT '订单日期',
  `Plate` varchar(7) DEFAULT NULL COMMENT '车牌号',
  `VIN` char(17) DEFAULT NULL COMMENT '车架号',
  `Owner` varchar(4) DEFAULT NULL COMMENT '车主',
  `Phone` char(11) DEFAULT NULL COMMENT '联系方式',
  `Description` varchar(50) DEFAULT NULL COMMENT '状况描述',
  `RepairStaffID` int DEFAULT NULL COMMENT '维修员工（记录ID）',
  `RepairTime` int DEFAULT '0',
  `QualityDetail` varchar(50) DEFAULT NULL COMMENT '质检描述',
  `QualityStaffID` int DEFAULT NULL COMMENT '质检员工（记录ID）',
  `Status` int DEFAULT NULL COMMENT '订单状态\n',
  PRIMARY KEY (`OrderID`),
  KEY `QualityStaffID_idx` (`RepairStaffID`, `QualityStaffID`)
) COMMENT = '订单列表';

CREATE TABLE `repair_part_storage` (
  `RepairPartID` int NOT NULL AUTO_INCREMENT,
  `PartName` varchar(9) DEFAULT NULL COMMENT '零件名称',
  `Price` int DEFAULT NULL COMMENT '价格',
  `Num` int DEFAULT NULL COMMENT '库存',
  `Req` int DEFAULT '0',
  PRIMARY KEY (`RepairPartID`),
  UNIQUE KEY `PartName_UNIQUE` (`PartName`)
) COMMENT = '库存表';

CREATE TABLE `repair_record` (
  `id_RepairRecord` int NOT NULL AUTO_INCREMENT,
  `OrderID` int DEFAULT NULL COMMENT '订单编号',
  `RepairPartID` int DEFAULT NULL COMMENT '零部件编号',
  `Num` int DEFAULT NULL COMMENT '使用数量',
  PRIMARY KEY (`id_RepairRecord`),
  KEY `OrderID_idx` (`OrderID`),
  KEY `RepairPartID_idx` (`RepairPartID`),
  CONSTRAINT `OrderID` FOREIGN KEY (`OrderID`) REFERENCES `order_list` (`OrderID`),
  CONSTRAINT `RepairPartID` FOREIGN KEY (`RepairPartID`) REFERENCES `repair_part_storage` (`RepairPartID`)
) COMMENT = '维修记录';

CREATE TABLE `user` (
  `UserID` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(6) DEFAULT NULL,
  `UserName` varchar(12) DEFAULT NULL,
  `PassWord` varchar(12) DEFAULT NULL,
  `Role` int DEFAULT NULL COMMENT '身份',
  PRIMARY KEY (`UserID`),
  UNIQUE KEY `UserName_UNIQUE` (`UserName`)
) COMMENT = '用户，即员工列表';
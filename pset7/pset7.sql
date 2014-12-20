-- MySQL dump 10.14  Distrib 5.5.32-MariaDB, for Linux (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.32-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `user_history`
--

DROP TABLE IF EXISTS `user_history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_history` (
  `surrogate_id` varchar(32) COLLATE utf8_unicode_ci NOT NULL,
  `user_id` int(10) unsigned NOT NULL,
  `transaction_date` datetime NOT NULL,
  `name` char(15) COLLATE utf8_unicode_ci NOT NULL,
  `symbol` char(8) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(15) unsigned NOT NULL,
  `credit` decimal(65,4) unsigned NOT NULL,
  `debit` decimal(65,4) unsigned NOT NULL,
  `transaction_type` char(15) COLLATE utf8_unicode_ci NOT NULL,
  `fill_price` decimal(65,4) unsigned NOT NULL,
  PRIMARY KEY (`surrogate_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_history`
--

LOCK TABLES `user_history` WRITE;
/*!40000 ALTER TABLE `user_history` DISABLE KEYS */;
INSERT INTO `user_history` VALUES ('192014-12-19 18:01:16DEPOSIT',19,'2014-12-19 18:01:16','DEPOSIT','',0,10000.0000,0.0000,'',0.0000),('62014-12-19 16:22:34GOOG',6,'2014-12-19 16:22:34','Google Inc.','GOOG',10,5163.5000,0.0000,'',516.3500),('62014-12-19 17:15:12GOOG',6,'2014-12-19 17:15:12','Google Inc.','GOOG',1,0.0000,516.3500,'',516.3500),('62014-12-19 17:20:46MSFT',6,'2014-12-19 17:20:46','Microsoft Corpo','MSFT',5,238.3000,0.0000,'',47.6600),('62014-12-19 17:22:14CAT',6,'2014-12-19 17:22:14','Caterpillar, In','CAT',10,0.0000,917.1000,'',91.7100),('62014-12-19 17:24:37BA',6,'2014-12-19 17:24:37','Boeing Company','BA',25,0.0000,3155.7500,'',126.2300),('62014-12-20 00:53:07DEPOSIT',6,'2014-12-20 00:53:07','DEPOSIT','',0,0.0000,100.0000,'',0.0000),('62014-12-20 01:02:13DEPOSIT',6,'2014-12-20 01:02:13','DEPOSIT','',0,0.0000,100.0000,'',0.0000),('62014-12-20 01:23:18WITHDRAWAL',6,'2014-12-20 01:23:18','DEPOSIT','',0,0.0000,100.0000,'',0.0000),('62014-12-20 01:33:27DEPOSIT',6,'2014-12-20 01:33:27','TRANSFER','',0,100.0000,0.0000,'',0.0000),('62014-12-20 01:35:39WITHDRAWAL',6,'2014-12-20 01:35:39','TRANSFER','',0,0.0000,100.0000,'',0.0000),('62014-12-20 01:36:26WITHDRAWAL',6,'2014-12-20 01:36:26','TRANSFER','',0,0.0000,100.0000,'',0.0000),('62014-12-20 01:37:18WITHDRAWAL',6,'2014-12-20 01:37:18','TRANSFER','',0,0.0000,100.0000,'',0.0000),('62014-12-20 01:41:08WITHDRAWAL',6,'2014-12-20 01:41:08','TRANSFER','',0,0.0000,100.0000,'',0.0000),('62014-12-20 01:41:36GOOG',6,'2014-12-20 01:41:36','Google Inc.','GOOG',10,0.0000,5163.5000,'',516.3500),('62014-12-20 01:44:11WITHDRAWAL',6,'2014-12-20 01:44:11','TRANSFER','',0,0.0000,1.0000,'',0.0000),('62014-12-20 01:47:37WITHDRAWAL',6,'2014-12-20 01:47:37','TRANSFER','',0,0.0000,1.0000,'',0.0000),('62014-12-20 01:48:48WITHDRAWAL',6,'2014-12-20 01:48:48','TRANSFER','',0,0.0000,100.0000,'',0.0000),('62014-12-20 01:49:00DEPOSIT',6,'2014-12-20 01:49:00','TRANSFER','',0,10000.0000,0.0000,'',0.0000),('62014-12-20 02:03:44GOOG',6,'2014-12-20 02:03:44','Google Inc.','GOOG',1,0.0000,516.3500,'',516.3500),('62014-12-20 02:17:54FB',6,'2014-12-20 02:17:54','Facebook, Inc.','FB',25,0.0000,1997.0000,'',79.8800),('62014-12-20 02:21:55GOOG',6,'2014-12-20 02:21:55','Google Inc.','GOOG',10,0.0000,5163.5000,'',516.3500),('62014-12-20 02:31:21CAT',6,'2014-12-20 02:31:21','Caterpillar, In','CAT',1,0.0000,91.7100,'',91.7100),('62014-12-20 02:37:30GOOG',6,'2014-12-20 02:37:30','Google Inc.','GOOG',1,0.0000,516.3500,'BUY',516.3500),('62014-12-20 02:43:53FB',6,'2014-12-20 02:43:53','Facebook, Inc.','FB',1,0.0000,79.8800,'BUY',79.8800),('62014-12-20 02:46:02FB',6,'2014-12-20 02:46:02','Facebook, Inc.','FB',2,159.7600,0.0000,'SELL',79.8800),('62014-12-20 02:57:52DEPOSIT',6,'2014-12-20 02:57:52','TRANSFER','',0,15000.0000,0.0000,'DEPOSIT',0.0000),('62014-12-20 03:01:30FB',6,'2014-12-20 03:01:30','Facebook, Inc.','FB',1,0.0000,79.8800,'BUY',79.8800),('62014-12-20 03:03:35MSFT',6,'2014-12-20 03:03:35','Microsoft Corpo','MSFT',2,0.0000,95.3200,'BUY',47.6600),('62014-12-20 03:10:18CAT',6,'2014-12-20 03:10:18','Caterpillar, In','CAT',2,0.0000,183.4200,'BUY',91.7100),('62014-12-20 03:12:37GOOG',6,'2014-12-20 03:12:37','Google Inc.','GOOG',2,1032.7000,0.0000,'SELL',516.3500),('62014-12-20 03:14:13WITHDRAWAL',6,'2014-12-20 03:14:13','TRANSFER','',0,0.0000,100.0000,'WITHDRAWAL',0.0000),('62014-12-20 03:14:25DEPOSIT',6,'2014-12-20 03:14:25','TRANSFER','',0,5.0000,0.0000,'DEPOSIT',0.0000),('62014-12-20 03:50:07DEPOSIT',6,'2014-12-20 03:50:07','TRANSFER','',0,3489.0000,0.0000,'DEPOSIT',0.0000),('62014-12-20 03:50:15DEPOSIT',6,'2014-12-20 03:50:15','TRANSFER','',0,3489.0000,0.0000,'DEPOSIT',0.0000);
/*!40000 ALTER TABLE `user_history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_portfolios`
--

DROP TABLE IF EXISTS `user_portfolios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_portfolios` (
  `user_id` int(10) unsigned NOT NULL,
  `symbol` char(8) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(15) unsigned NOT NULL,
  `surrogate_id` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`surrogate_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_portfolios`
--

LOCK TABLES `user_portfolios` WRITE;
/*!40000 ALTER TABLE `user_portfolios` DISABLE KEYS */;
INSERT INTO `user_portfolios` VALUES (6,'AAPL',50,'6AAPL'),(6,'BA',25,'6BA'),(6,'BAC',100,'6BAC'),(6,'CAT',13,'6CAT'),(6,'CMA',100,'6CMA'),(6,'FB',23,'6FB'),(6,'GOOG',82,'6GOOG'),(6,'GS',93,'6GS'),(6,'MSFT',107,'6MSFT');
/*!40000 ALTER TABLE `user_portfolios` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `hash` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=20 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'caesar','$1$50$GHABNWBNE/o4VL7QjmQ6x0',10000.0000),(2,'hirschhorn','$1$50$lJS9HiGK6sphej8c4bnbX.',10000.0000),(3,'jharvard','$1$50$RX3wnAMNrGIbgzbRYrxM1/',10000.0000),(4,'malan','$1$HA$azTGIMVlmPi9W9Y12cYSj/',10000.0000),(5,'milo','$1$HA$6DHumQaK4GhpX8QE23C8V1',10000.0000),(6,'skroob','$1$50$euBi4ugiJmbpIbvTTfmfI.',56254.0700),(7,'zamyla','$1$50$uwfqB45ANW.9.6qaQ.DcF.',10000.0000),(15,'computer','$1$HYN6qVwS$mzqiVSoHxOooU9mcRcYPN/',10000.0000),(16,'user_test','$1$SdaP87WQ$jdoiVT05k3MESvEqWxZ.x/',10000.0000),(17,'new_user','$1$VHoinHH9$c8cKWPg5NC5dDxTakZm6D.',100000.0000),(18,'a_new_user','$1$lMHt.PtU$zdGGizNNWz5q5aZXmc.D11',10000.0000),(19,'pizza01','$1$mmfS34/y$UhINNN9.aFj5phkNjN7pt/',10000.0000);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-12-20  4:36:06

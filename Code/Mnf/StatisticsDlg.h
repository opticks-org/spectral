/*
 * The information in this file is
 * Copyright(c) 2010 Ball Aerospace & Technologies Corporation
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */

#ifndef STATISTICSDLG_H
#define STATISTICSDLG_H

#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>

#include <vector>
#include <string>

class StatisticsDlg : public QDialog
{
   Q_OBJECT

public:
   StatisticsDlg(std::string rasterName, QWidget* parent = 0);
   ~StatisticsDlg();

   int getRowFactor() const;
   int getColumnFactor() const;
   std::string getAoiName() const;
   std::string getDarkCurrentDataName() const;

   virtual void accept();

protected slots:
   void loadRaster();
   void rasterChanged(const QString& rasterName);

private:
   QComboBox* mpRasterCombo;
   QRadioButton* mpFactorRadio;
   QSpinBox* mpRowSpin;
   QSpinBox* mpColumnSpin;
   QRadioButton* mpAoiRadio;
   QComboBox* mpAoiCombo;
};

#endif

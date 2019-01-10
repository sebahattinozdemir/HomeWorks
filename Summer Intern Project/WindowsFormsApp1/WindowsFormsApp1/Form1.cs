using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.OleDb;
using OfficeOpenXml;
using System.IO;
using OfficeOpenXml.Style;
using System.Globalization;
using OfficeOpenXml.FormulaParsing.Excel.Functions.DateTime;

namespace WindowsFormsApp1
{
    public partial class QAReport : Form
    {

      
        public string path;  /* to store user selected file path*/

        public QAReport()
        {
            InitializeComponent();
        }



/************************************************************************************************************************************************************************************************************************************************/


        class Data /*To store excel Data with list */ 
        {

         public   string nameSurname { get; set; }
         public   string department { get; set; }
         public   string date { get; set; }
         public   string sHour { get; set; } /*startHour*/
         public   string eHour { get; set; } /*exit Hour*/
         public   string totalHour { get; set; }
            List<Data> d1 = new List<Data>();
        }

 /************************************************************************************************************************************************************************************************************************************************/
           
       /* for browse button*/
        private void button1_Click_1(object sender, EventArgs e)
        {

            String input = string.Empty;
            OpenFileDialog dialog = new OpenFileDialog();

            dialog.Filter = "xlsx files (*.xlsx)|*.xlsx|All files (*.*)|*.*";

            dialog.InitialDirectory = "C:";
            dialog.Title = "Select a text file";

            if (dialog.ShowDialog() == DialogResult.OK)
                path=(dialog.FileName);


            if (dialog.FileName == String.Empty)
              return; /*user didn't select a file to opena*/ 

        }

/************************************************************************************************************************************************************************************************************************************************/

        // for process button

       List<Data> data = new List<Data>(); /*To store excel data to in list*/

        private void button2_Click(object sender, EventArgs e)
        {            
            ExcelPackage package = new ExcelPackage(new FileInfo(path));
            ExcelWorksheet wsheet3 = package.Workbook.Worksheets.FirstOrDefault();
                  
            string adSoyad = null;
            string bolum = null;
            string tarih = null;
            string girisSaati = null;
            string cikisSaati = null;
            string sure = null;

            for (int i = wsheet3.Dimension.Start.Row; i <= wsheet3.Dimension.End.Row-5; i++)
            {
                adSoyad       = wsheet3.Cells[i+4,3].Value.ToString();
                bolum         = wsheet3.Cells[i+4, 5].Value.ToString();
                tarih         = wsheet3.Cells[i + 4, 7].Value.ToString();
                girisSaati    = wsheet3.Cells[i + 4, 8].Value.ToString();
                cikisSaati    = wsheet3.Cells[i + 4, 9].Value.ToString();
                sure          = wsheet3.Cells[i + 4, 11].Value.ToString();

                data.Add(new Data() { nameSurname = adSoyad, department = bolum, date = tarih, sHour = girisSaati, eHour = cikisSaati, totalHour = sure });

                         
            }
            


        }

/************************************************************************************************************************************************************************************************************************************************/

        class Results /*To store excel Data with list */
        {


            public string NameSurname { get; set; }
            public string Date { get; set; }
            public TimeSpan d { get; set; }                
            public int      Week{ get; set; }           
            List<Results> d2 = new List<Results>();
        }

        List<Results> d2 = new List<Results>();

        class writer
        {
           public IEnumerable<Data> data;
           public ExcelRange Rng;
           public ExcelPackage ExcelPkg = new ExcelPackage();
           public IEnumerable<Results> res;


            public string Path { get;  set; }
           
           public void createExcelFile()
            {
               
                ExcelWorksheet wsSheet1 = ExcelPkg.Workbook.Worksheets.Add("Sheet1");             
                             
                // for sheet1 data from taken the input excel file
                Rng = wsSheet1.Cells[1, 1];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "ADSOYAD";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);


                Rng = wsSheet1.Cells[1, 2];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "BOLUM";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);


                Rng = wsSheet1.Cells[1, 3];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "TARIH";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);


                Rng = wsSheet1.Cells[1, 4];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "GIRIS";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);


                Rng = wsSheet1.Cells[1, 5];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "CIKIS";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);


                Rng = wsSheet1.Cells[1, 6];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "SURE";
                Rng.Style.Font.Size = 10;              
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                int iterator = 0;
                foreach (Data daily in data)
                {
             
                    Rng = wsSheet1.Cells[iterator + 2, 1];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                    Rng.Value = daily.nameSurname;
                    Rng.Style.Font.Size = 10;
                    Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                    Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                    Rng = wsSheet1.Cells[iterator + 2, 2];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                    Rng.Value = daily.department;
                    Rng.Style.Font.Size = 10;
                    Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                    Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                    Rng = wsSheet1.Cells[iterator + 2, 3];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                    Rng.Value = daily.date;
                    Rng.Style.Font.Size = 10;       
                    Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                    Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                    Rng = wsSheet1.Cells[iterator + 2, 4];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                    Rng.Value = daily.sHour;
                    Rng.Style.Font.Size = 10;                 
                    Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                    Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                    Rng = wsSheet1.Cells[iterator + 2, 5];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                    Rng.Value = daily.eHour;
                    Rng.Style.Font.Size = 10;             
                    Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                    Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                    Rng = wsSheet1.Cells[iterator + 2, 6];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                    Rng.Value = daily.totalHour;
                    Rng.Style.Font.Size = 10;                
                    Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                    Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                    iterator++;
                  
                }

                wsSheet1.Protection.AllowSelectLockedCells = false;                                            
                ExcelPkg.SaveAs(new FileInfo(Path + @".xlsx"));

            }
/**********************************************************************************************************************************************************************************************************************************************************/
            List<Results> Latency = new List<Results>();
            List<Results> Compansated = new List<Results>();
          public  List<Data> datas = new List<Data>();
            public void daily()
            {
                ExcelWorksheet wsSheet2 = ExcelPkg.Workbook.Worksheets.Add("Daily");

                Rng = wsSheet2.Cells[1, 1];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "NAME";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);


                Rng = wsSheet2.Cells[1, 2];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "DATE";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);


                Rng = wsSheet2.Cells[1, 3];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "DATE OF DAY";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                Rng = wsSheet2.Cells[1, 4];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "LATENCY";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                Rng = wsSheet2.Cells[1, 5];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "COMPANSATED";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                Rng = wsSheet2.Cells[1, 6];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "LACKING TIME";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                Rng = wsSheet2.Cells[1, 7];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "STATUS";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                
                /*Getting name value and saving to daily sheet*/
                int i = 2;
                foreach (Data daily in data)
                {

                    Rng = wsSheet2.Cells[i++, 1];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                    Rng.Value = daily.nameSurname;
                    Rng.Style.Font.Size = 10;
                    Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                    Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);


                }

                /*Getting date value from excel file and saving to daily sheet*/
                i = 2;
                foreach (Data daily in data)
                {

                    Rng = wsSheet2.Cells[i++, 2];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                    Rng.Value = daily.date;
                    Rng.Style.Font.Size = 10;
                    Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                    Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);


                }

                /*name of the day*/
                i = 2;
                foreach (Data daily in data)
                {

                    Rng = wsSheet2.Cells[i++, 3];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                    DateTime Date = DateTime.Parse(daily.date);
                    DayOfWeek day = Date.DayOfWeek;
                    Rng.Value = day;
                    Rng.Style.Font.Size = 10;
                    Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                    Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);


                }

                /*Checking the person if he is late in that day*/
                /*latency*/
                i = 2;
                int j = 2;
                foreach (Data daily in data)
                {

                    Rng = wsSheet2.Cells[i++, 4];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                    DateTime Date5 = DateTime.Parse(daily.date);
                    DateTime Date = DateTime.Parse(daily.sHour);
                  
                    int Year = Date.Year;
                    int Month = Date.Month;
                    int Day = Date.Day;
                    Double Hour = Date.Hour;
                    Double Minutes = Date.Minute;
                    Double Seconds = Date.Second;
                    Double MiliSeconds = Date.Millisecond;

                    System.DateTime Date1 = new System.DateTime(Year,Month,Day,8, 0, 0);
                    TimeSpan dif = Date.Subtract(Date1);



                    Latency.Add(new Results() { NameSurname = daily.nameSurname, d = dif ,Date = daily.date, Week = GetIso8601WeekOfYear(Date5) });


                    if (dif.Hours < 0 || dif.Minutes < 0 || dif.Seconds < 0 )
                        Rng.Value = "00:00:00";
                        
                    else   Rng.Value = Convert.ToString(dif);

                    Rng.Style.Font.Size = 10;
                    Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                    Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                    /*Checking that the person if he is late, in that day check that if he compansted the time or not*/
                    /*Compansated*/

                    Rng = wsSheet2.Cells[j++, 5];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                    DateTime date5 = DateTime.Parse(daily.date);
                    DateTime date = DateTime.Parse(daily.eHour);

                    int year = date.Year;
                    int month = date.Month;
                    int day = date.Day;
                    Double hour = date.Hour;
                    Double minutes = date.Minute;
                    Double seconds = date.Second;
                    Double miliSeconds = date.Millisecond;

                    System.DateTime date1 = new System.DateTime(year, month, day, 17, 0, 0);
                    TimeSpan Dif = date.Subtract(date1);
                    Compansated.Add(new Results() { NameSurname = daily.nameSurname, Date = daily.date,d = Dif, Week = GetIso8601WeekOfYear(date5) });

                    if (Dif.Hours < 0 || Dif.Minutes < 0 || Dif.Seconds < 0)
                        Rng.Value = "00:00:00";

                    else Rng.Value = Convert.ToString(Dif);

                    Rng.Style.Font.Size = 10;
                    Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                    Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);
                  
                }

                
                /*This loop does if latency  is greater than compansated it substracts compansated time from latency time else engineer worked 8.30 hour in that day and 
                  show it 0:00:00 time scale like this*/
                for(i =0 ; i < Latency.Count;i++)
                {
                    if(Latency[i].d  > Compansated[i].d)
                    {

                         Latency[i].d = Latency[i].d.Subtract(Compansated[i].d); 

                    }

                    else
                    {
                        Latency[i].d = TimeSpan.Zero;
                    }
                              
                }
                /*Lacking Time*/
                i = 2;
                foreach (Results daily in Latency)
                {

                    Rng = wsSheet2.Cells[i++, 6];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);

                    if (daily.d == TimeSpan.Zero)
                    {
                        Rng.Value = Convert.ToString(daily.d);
                        Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                        Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.Green);
                    }
                    else
                    {
                        Rng.Value = Convert.ToString(daily.d);
                        Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                        Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.Red);

                    }

                }

                /*status*/
                i = 2;
                foreach (Data daily in data)
                {

                    Rng = wsSheet2.Cells[i++, 7];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);

                    TimeSpan Interval = TimeSpan.Parse(daily.totalHour);
                                       
                    TimeSpan BaseInterval = new TimeSpan(9,0,0);
                    int result = TimeSpan.Compare(BaseInterval, Interval);

                    if (result == 1 ) 
                    {
                        Rng.Value = "POOR";
                        Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                        Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.Red);

                    }
                    else /*for  0 */
                    {
                        Rng.Value = "EXCELLENT";
                        Rng.Style.Font.Size = 10;
                        Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                        Rng.Style.Fill.BackgroundColor.SetColor(Color.Green);
                        
                    }

                }

                
                wsSheet2.Protection.AllowSelectLockedCells = false;
                ExcelPkg.SaveAs(new FileInfo(Path + @".xlsx"));
            }

/**********************************************************************************************************************************************************************************************************************************************************/

            // This presumes that weeks start with Monday.
            // Week 1 is the 1st week of the year with a Thursday in it.

            public static int GetIso8601WeekOfYear(DateTime time)
            {
                // Seriously cheat.  If its Monday, Tuesday or Wednesday, then it'll 
                // be the same week# as whatever Thursday, Friday or Saturday are,
                // and we always get those right
                DayOfWeek day = CultureInfo.InvariantCulture.Calendar.GetDayOfWeek(time);
                if (day >= DayOfWeek.Monday && day <= DayOfWeek.Wednesday)
                {
                    time = time.AddDays(3);
                }

                // Return the week of our adjusted day
                return CultureInfo.InvariantCulture.Calendar.GetWeekOfYear(time, CalendarWeekRule.FirstFourDayWeek, DayOfWeek.Monday);
            }


            public void weekly()
            {

                ExcelWorksheet wsSheet3 = ExcelPkg.Workbook.Worksheets.Add("Weekly");

                Rng = wsSheet3.Cells[1, 1];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "NAME";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);


                Rng = wsSheet3.Cells[1, 2];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "MONTH";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                Rng = wsSheet3.Cells[1, 3];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "WEEK";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                
                Rng = wsSheet3.Cells[1, 4];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "LATENCY";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                

                Rng = wsSheet3.Cells[1, 5];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "STATUS";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                /*calculations goes here*/
                /*Getting name value and saving to daily sheet*/
                int i = 2;
                foreach (Data daily in data)
                {

                    Rng = wsSheet3.Cells[i++, 1];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                    Rng.Value = daily.nameSurname;
                    Rng.Style.Font.Size = 10;
                    Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                    Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                }
                /*Getting month name and saving to weeklysheet */

                 i = 2;
                foreach (Data daily in data)
                {

                    Rng = wsSheet3.Cells[i++, 2];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);

                    DateTime Date = DateTime.Parse(daily.date);

                    int Month = Date.Month;

                    switch (Month)
                    {
                        case 1:
                             Rng.Value = "January";
                            break;
                        case 2:
                            Rng.Value = "February";
                            break;
                        case 3:
                            Rng.Value = "March";
                            break;
                        case 4:
                            Rng.Value = "April";
                            break;
                        case 5:
                            Rng.Value = "May";
                            break;
                        case 6:
                            Rng.Value = "June";
                            break;
                        case 7:
                            Rng.Value = "July";
                            break;
                        case 8:
                            Rng.Value = "August";
                            break;
                        case 9:
                            Rng.Value = "September";
                            break;
                        case 10:
                            Rng.Value = "October";
                            break;
                        case 11:
                            Rng.Value = "November";
                            break;
                        case 12:
                            Rng.Value = "December";
                            break;

                        default:
                            Rng.Value = "Unknown Date, Please Check the Date";
                            break;

                    }

                   
                    Rng.Style.Font.Size = 10;
                    Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                    Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);


                }


                /*Getting Week Number and saving to weekly sheet*/

                    i = 2;
                foreach (Data daily in data)
                {

                    Rng = wsSheet3.Cells[i++, 3];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);

                    DateTime Date = DateTime.Parse(daily.date);
                   
                    Rng.Value = GetIso8601WeekOfYear(Date);

                    Rng.Style.Font.Size = 10;
                    Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                    Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);


                }

                /*Check Weekly Latency*/


                i = 2;
                TimeSpan sumOfLatency;
                foreach(Data daily in data) {
                    sumOfLatency = new TimeSpan ();

                    DateTime Date = DateTime.Parse(daily.date);
                    int  day= GetIso8601WeekOfYear(Date);

                    foreach (Results weekly in Latency)
                    {
                        if (day == weekly.Week && daily.nameSurname == weekly.NameSurname)
                            sumOfLatency+=weekly.d;                     
                    }

                    if (sumOfLatency > TimeSpan.Zero)
                    {
                        Rng = wsSheet3.Cells[i++, 4];
                        Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                        Rng.Value = Convert.ToString(sumOfLatency);
                        Rng.Style.Font.Size = 10;
                        Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                        Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.Red);
                    }

                    else
                    {
                        Rng = wsSheet3.Cells[i++, 4];
                        Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                        Rng.Value = Convert.ToString(sumOfLatency);
                        Rng.Style.Font.Size = 10;
                        Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                        Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.Green);
                    }

                }


                /*Check Status*/


                i = 2;
              
                foreach (Data daily in data)
                {
                    sumOfLatency = new TimeSpan();

                    DateTime Date = DateTime.Parse(daily.date);
                    int day = GetIso8601WeekOfYear(Date);

                    foreach (Results weekly in Latency)
                    {
                        if (day == weekly.Week && daily.nameSurname == weekly.NameSurname)
                            sumOfLatency += weekly.d;
                    }
                    


                    if(sumOfLatency > TimeSpan.Zero)
                    {
                        Rng = wsSheet3.Cells[i++, 5];
                        Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                        Rng.Value = "POOR";
                        Rng.Style.Font.Size = 10;
                        Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                        Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.Red);

                    }

                    else
                    {
                        Rng = wsSheet3.Cells[i++, 5];
                        Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                        Rng.Value = "EXCELLENT";
                        Rng.Style.Font.Size = 10;
                        Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                        Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.Green);
                    }

                }

                wsSheet3.Protection.AllowSelectLockedCells = false;
                ExcelPkg.SaveAs(new FileInfo(Path + @".xlsx"));
            }

            
/**********************************************************************************************************************************************************************************************************************************************************/
            public void montly()
            {
                ExcelWorksheet wsSheet4 = ExcelPkg.Workbook.Worksheets.Add("Monthly");

                Rng = wsSheet4.Cells[1, 1];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "NAME";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);


                /*Getting name value and saving to daily sheet*/


                int i = 2;
                foreach (Data daily in data)
                {

                    Rng = wsSheet4.Cells[i++, 1];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                    Rng.Value = daily.nameSurname;
                    Rng.Style.Font.Size = 10;
                    Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                    Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                }




                /*
                int i = 2;               
                int j = 2;
                for (i = 0; i <datas.Count-1; i++)
                {
                    if (datas[i].nameSurname == datas[i+1].nameSurname)
                        continue;
                    else
                    {
                        Rng = wsSheet4.Cells[j++, 1];
                        Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                        Rng.Value = datas[i].nameSurname;
                        Rng.Style.Font.Size = 10;
                        Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                        Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);
                    }

                }
                */

                /*Getting Month and saving to Monthly sheet*/

                Rng = wsSheet4.Cells[1, 3];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "MONTH";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);

                i = 2;
                foreach (Data daily in data)
                {

                    Rng = wsSheet4.Cells[i++, 2];
                    Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);

                    DateTime Date = DateTime.Parse(daily.date);

                    int Month = Date.Month;

                    switch (Month)
                    {
                        case 1:
                            Rng.Value = "January";
                            break;
                        case 2:
                            Rng.Value = "February";
                            break;
                        case 3:
                            Rng.Value = "March";
                            break;
                        case 4:
                            Rng.Value = "April";
                            break;
                        case 5:
                            Rng.Value = "May";
                            break;
                        case 6:
                            Rng.Value = "June";
                            break;
                        case 7:
                            Rng.Value = "July";
                            break;
                        case 8:
                            Rng.Value = "August";
                            break;
                        case 9:
                            Rng.Value = "September";
                            break;
                        case 10:
                            Rng.Value = "October";
                            break;
                        case 11:
                            Rng.Value = "November";
                            break;
                        case 12:
                            Rng.Value = "December";
                            break;

                        default:
                            Rng.Value = "Unknown Date, Please Check the Date";
                            break;

                    }


                    Rng.Style.Font.Size = 10;
                    Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                    Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);


                }

                /*
                List<Data> d1 = new List<Data>();
                d1 = datas;
               int  k = 2;
                d1 = (from e in d1 // to get distinct months from the list we sorted the list by date
                        orderby e.date
                        select e).ToList();

                for (i = 0; i < d1.Count - 1; i++)
                {
                    
                    DateTime Date = DateTime.Parse(d1[i].date);

                    int Month = Date.Month;

                    DateTime Date1 = DateTime.Parse(d1[i+1].date);

                    int Month1 = Date1.Month;
                    if (Month == Month1)
                        continue;
                    else
                    {
                        Rng = wsSheet4.Cells[1, k++];
                        Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);

                        switch (Month)
                        {
                            case 1:
                                Rng.Value = "January";
                                break;
                            case 2:
                                Rng.Value = "February";
                                break;
                            case 3:
                                Rng.Value = "March";
                                break;
                            case 4:
                                Rng.Value = "April";
                                break;
                            case 5:
                                Rng.Value = "May";
                                break;
                            case 6:
                                Rng.Value = "June";
                                break;
                            case 7:
                                Rng.Value = "July";
                                break;
                            case 8:
                                Rng.Value = "August";
                                break;
                            case 9:
                                Rng.Value = "September";
                                break;
                            case 10:
                                Rng.Value = "October";
                                break;
                            case 11:
                                Rng.Value = "November";
                                break;
                            case 12:
                                Rng.Value = "December";
                                break;

                            default:
                                Rng.Value = "Unknown Date, Please Check the Date";
                                break;

                        }
                        Rng.Style.Font.Size = 10;
                        Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                        Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);
                    }

                }
                */

                Rng = wsSheet4.Cells[1, 3];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "LATENCY";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);
               
                Rng = wsSheet4.Cells[1, 4];
                Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                Rng.Value = "STATUS";
                Rng.Style.Font.Size = 10;
                Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.White);



                /*Calculating the montly latency*/
                /**/
                i = 2;
                             
                TimeSpan sumOfLatency;

                foreach (Data daily in data)
                {
                    sumOfLatency = new TimeSpan();


                    DateTime Date = DateTime.Parse(daily.date);

                    int Month = Date.Month;
                   
                    foreach (Results weekly in Latency)
                    {
                        DateTime Date1 = DateTime.Parse(weekly.Date);

                        int Month1 = Date1.Month;

                        if (Month == Month1 && daily.nameSurname == weekly.NameSurname)
                                        sumOfLatency+= weekly.d;

                    }

                    if (sumOfLatency > TimeSpan.Zero)
                    {
                        Rng = wsSheet4.Cells[i++, 3];
                        Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                        Rng.Value = Convert.ToString(sumOfLatency);
                        Rng.Style.Font.Size = 10;
                        Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                        Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.Red);

                    }

                    else
                    {
                        Rng = wsSheet4.Cells[i++, 3];
                        Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                        Rng.Value = Convert.ToString(sumOfLatency);
                        Rng.Style.Font.Size = 10;
                        Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                        Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.Green);
                    }

                }





                /*Calculating the Status*/

                i = 2;

              
                foreach (Data daily in data)
                {
                    sumOfLatency = new TimeSpan();


                    DateTime Date = DateTime.Parse(daily.date);

                    int Month = Date.Month;

                    foreach (Results weekly in Latency)
                    {
                        DateTime Date1 = DateTime.Parse(weekly.Date);

                        int Month1 = Date1.Month;

                        if (Month == Month1 && daily.nameSurname == weekly.NameSurname)
                            sumOfLatency += weekly.d;

                    }

                    if (sumOfLatency > TimeSpan.Zero)
                    {
                        Rng = wsSheet4.Cells[i++, 4];
                        Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                        Rng.Value = "POOR";
                        Rng.Style.Font.Size = 10;
                        Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                        Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.Red);

                    }

                    else
                    {
                        Rng = wsSheet4.Cells[i++, 4];
                        Rng.Style.Border.BorderAround(ExcelBorderStyle.Thin);
                        Rng.Value = "EXCELLENT";
                        Rng.Style.Font.Size = 10;
                        Rng.Style.Fill.PatternType = OfficeOpenXml.Style.ExcelFillStyle.Solid;
                        Rng.Style.Fill.BackgroundColor.SetColor(System.Drawing.Color.Green);
                    }

                }


         



                wsSheet4.Protection.AllowSelectLockedCells = false;
                ExcelPkg.SaveAs(new FileInfo(Path + @".xlsx"));
            }

/**********************************************************************************************************************************************************************************************************************************************************/

        }

/**********************************************************************************************************************************************************************************************************************************************************/

        private void button3_Click(object sender, EventArgs e)
        {
            writer a = new writer();
            a.Path = path;
            a.data = data;
            a.datas = data;
            a.res = d2;
            a.createExcelFile();
            a.daily();
            a.weekly();
            a.montly();

            Console.WriteLine("Finish");

        }

/**********************************************************************************************************************************************************************************************************************************************************/

    }
}

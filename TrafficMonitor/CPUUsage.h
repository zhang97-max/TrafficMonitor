#pragma once
#include <Pdh.h>
#include <PdhMsg.h>

class CPdhQuery
{
public:
    CPdhQuery(LPCTSTR _fullCounterPath);
    virtual ~CPdhQuery();

protected:
    bool Initialize();
    bool QueryValue(double& value);

protected:
    HQUERY query = nullptr;
    HCOUNTER counter = nullptr;
    bool isInitialized = false;
    CString fullCounterPath;
};

class CCPUUsage : public CPdhQuery
{
public:
    CCPUUsage();

    ~CCPUUsage()
    {}

    void SetUseCPUTimes(bool use_get_system_times);		//���û�ȡCPU�����ʵķ�ʽ����ͨ��GetSystemTimes����Pdh
    int GetCpuUsage();

private:
    int GetCpuUsageByGetSystemTimes();
    bool GetCPUUsageByPdh(int& cpu_usage);

private:
    bool m_use_get_system_times{ true };		//�Ƿ�ʹ��GetSysTime���API����ȡCPU������

    FILETIME m_preidleTime{};
    FILETIME m_prekernelTime{};
    FILETIME m_preuserTime{};

};

class CCpuFreq : public CPdhQuery
{
public:
    CCpuFreq();

    // ���ô˺�����ȡCPUƵ�ʡ�
    // ע�⣺�ڶ��ε��ô˺�����ʼ���ܻ�ȡ��ֵ�����ε��õ�ʱ�䲻Ӧ���̣���ô���200����
    bool GetCpuFreq(float& freq);

private:
    float max_cpu_freq = 0;
};

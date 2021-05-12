#ifndef STDCAPTURE_H
#define STDCAPTURE_H
#ifdef _MSC_VER
#include <io.h>
#endif
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <fcntl.h>
#include <stdio.h>
#include <string>

class STDCapture
{
public:
    STDCapture(): m_capturing(false), m_init(false), m_oldStdOut(0), m_oldStdErr(0)
    {
        m_pipe[READ] = 0;
        m_pipe[WRITE] = 0;
        if (_pipe(m_pipe, 65536, O_BINARY) == -1)
            return;
        m_oldStdOut = _dup(_fileno(stdout));
        m_oldStdErr = _dup(_fileno(stderr));
        if (m_oldStdOut == -1 || m_oldStdErr == -1)
            return;

        m_init = true;
    }

    ~STDCapture()
    {
        if (m_capturing)
        {
            EndCapture();
        }
        if (m_oldStdOut > 0)
            _close(m_oldStdOut);
        if (m_oldStdErr > 0)
            _close(m_oldStdErr);
        if (m_pipe[READ] > 0)
            _close(m_pipe[READ]);
        if (m_pipe[WRITE] > 0)
            _close(m_pipe[WRITE]);
    }


    void BeginCapture()
    {
        if (!m_init)
            return;
        if (m_capturing)
            EndCapture();
        fflush(stdout);
        fflush(stderr);
        _dup2(m_pipe[WRITE], _fileno(stdout));
        _dup2(m_pipe[WRITE], _fileno(stderr));
        m_capturing = true;
    }

    bool EndCapture()
    {
        if (!m_init)
            return false;
        if (!m_capturing)
            return false;
        fflush(stdout);
        fflush(stderr);
        _dup2(m_oldStdOut, _fileno(stdout));
        _dup2(m_oldStdErr, _fileno(stderr));
        m_captured.clear();

        std::string buf;
        const int bufSize = 1024;
        buf.resize(bufSize);
        int bytesRead = 0;
        if (!_eof(m_pipe[READ]))
        {
            bytesRead = _read(m_pipe[READ], &(*buf.begin()), bufSize);
        }
        while(bytesRead == bufSize)
        {
            m_captured += buf;
            bytesRead = 0;
            if (!_eof(m_pipe[READ]))
            {
                bytesRead = _read(m_pipe[READ], &(*buf.begin()), bufSize);
            }
        }
        if (bytesRead > 0)
        {
            buf.resize(bytesRead);
            m_captured += buf;
        }
        m_capturing = false;
        return true;
    }

    std::string GetCapture() const
    {
        std::string::size_type idx = m_captured.find_last_not_of("\r\n");
        if (idx == std::string::npos)
        {
            return m_captured;
        }
        else
        {
            return m_captured.substr(0, idx+1);
        }
    }

private:
    enum PIPES { READ, WRITE };
    int m_pipe[2];
    int m_oldStdOut;
    int m_oldStdErr;
    bool m_capturing;
    bool m_init;
    std::string m_captured;
};

#endif // STDCAPTURE_H

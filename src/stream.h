#pragma once

#define __STDC_CONSTANT_MACROS
#define __STDC_FORMAT_MACROS


extern "C" { 
#include <libavutil/timestamp.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

#include <QString>

int stream(const QString &address, const QString &file);

static void log_packet(const AVFormatContext *fmt_ctx, const AVPacket *pkt, const char *tag);

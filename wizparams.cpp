#include <vector>
#include <QtWidgets>

#include "wizparams.h"
#include "shpproc.h"

bool wiz_params_c::write_settings(const wiz_params_c& wiz, const std::vector<shp_c*>& shp_files, const QString& fname)
{
	QJsonObject json;
	json["msg_path"] = wiz.msg_path;
	json["jpg_path"] = wiz.jpg_path;
	json["shp_path"] = wiz.shp_path;
	json["fname_pref"] = wiz.fname_pref;
	json["arrow_scale"] = wiz.arrow_scale;
	json["arrow_width"] = wiz.arrow_width;
	json["arrow_color"] = wiz.arrow_color.name();
	json["msg_num"] = wiz.msg;
	json["channel_idx"] = wiz.channel_idx;
	{
		const date_c& start = wiz.start;
		const date_c& stop = wiz.stop;
		char buf[100];
		sprintf(buf, "%4d-%02d-%02d %02d:%02d", start.m_year, start.m_mon, start.m_day, start.m_hour, start.m_mn);
		json["start_date"] = buf;
		sprintf(buf, "%4d-%02d-%02d %02d:%02d", stop.m_year, stop.m_mon, stop.m_day, stop.m_hour, stop.m_mn);
		json["stop_date"] = buf;
	}
	{
		QJsonArray arr;
		for (int i = 0; i < shp_files.size(); i++) {
			const shp_c* shp = shp_files[i];

			QJsonObject obj;
			obj["dbf_field"] = shp->m_dbf_field;
			obj["shp_name"] = shp->m_shp_name;
			obj["line_color"] = shp->m_line_color.name();
			obj["text_color"] = shp->m_text_color.name();
			obj["line_width"] = shp->m_line_width;
			obj["dash"] = shp->m_dash;
			obj["font_face"] = shp->m_font_face;
			obj["font_size"] = shp->m_font_size;
			arr.append(obj);
		}
		json["shp_files"] = arr;
	}
	bool ret = false;
	{
		QByteArray ba = QJsonDocument(json).toJson(QJsonDocument::Compact);
		QFile file(fname);
		if (file.open(QIODevice::WriteOnly) && file.write(ba) == ba.size())
			ret = true;
		file.close();
	}
	return ret;
}

bool wiz_params_c::read_settings(wiz_params_c& wiz, std::vector<shp_c*>& shp_files, const QString& fname)
{
	QString val;
	{
		QFile file;
		file.setFileName(fname);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			file.close();
			return false;
		}
		val = file.readAll();
		file.close();
	}
	QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
	QJsonObject json = doc.object();

	wiz.msg_path = json["msg_path"].toString();
	wiz.jpg_path = json["jpg_path"].toString();
	wiz.shp_path = json["shp_path"].toString();
	wiz.fname_pref = json["fname_pref"].toString();
	wiz.arrow_scale = json["arrow_scale"].toDouble();
	wiz.arrow_width = json["arrow_width"].toDouble();
	wiz.arrow_color = QColor(json["arrow_color"].toString());
	wiz.msg = json["msg_num"].toInt();
	wiz.channel_idx = json["channel_idx"].toInt();
	{
		QDateTime dt0 = QDateTime::fromString(json["start_date"].toString(), "yyyy-MM-dd hh:mm");
		QDateTime dt1 = QDateTime::fromString(json["stop_date"].toString(), "yyyy-MM-dd hh:mm");
		wiz.start = date_c(dt0.date().year(), dt0.date().month(), dt0.date().day(), dt0.time().hour(), dt0.time().minute());
		wiz.stop = date_c(dt1.date().year(), dt1.date().month(), dt1.date().day(), dt1.time().hour(), dt1.time().minute());
	}
	{
		QJsonArray arr = json["shp_files"].toArray();
		for (auto&& item : arr) {
			shp_c* shp = new shp_c();

			QJsonObject obj = item.toObject();
			shp->m_dbf_field = obj["dbf_field"].toString();
			shp->m_shp_name = obj["shp_name"].toString();
			QString cs = obj["line_color"].toString();
			shp->m_line_color = QColor(cs);
			cs = obj["text_color"].toString();
			shp->m_text_color = QColor(cs);
			shp->m_line_width = obj["line_width"].toDouble();
			shp->m_dash = obj["dash"].toInt();
			shp->m_font_face = obj["font_face"].toString();
			shp->m_font_size = obj["font_size"].toInt();

			shp_files.push_back(shp);
		}
	}
	return true;
}

